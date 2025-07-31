#include "PngImageFormatWriter.h"

#include "Logger.h"

#include <lodepng.h>
#include <tbb/parallel_for.h>

namespace crayg {

namespace internal {

struct PngWriteData {
    unsigned char *pixelBuffer;
    bool isOwning = false;
    lodepng::State state;
    int width;
    int height;
};

void appendImageMetadata(const ImageMetadata &imageMetadata, PngWriteData &writeData) {
    for (auto &metadataentry : imageMetadata) {
        const std::string key = metadataentry.first;
        const std::string value = fmt::format("{}", metadataentry.second);
        lodepng_add_text(&writeData.state.info_png, key.c_str(), value.c_str());
    }
}

template <typename ImageBufferType> struct ImageBufferTypeTrait {
    static int getWidth(const ImageBufferType &bufferType);
    static int getHeight(const ImageBufferType &bufferType);
    static PixelFormat getPixelFormat(const ImageBufferType &bufferType);
    static int getColorChannelCount(const ImageBufferType &bufferType);
    static void *getDataPtr(const ImageBufferType &bufferType);
};

template <> struct ImageBufferTypeTrait<PixelBuffer> {
    static int getWidth(const PixelBuffer &pixelBuffer) {
        return pixelBuffer.getWidth();
    }

    static int getHeight(const PixelBuffer &pixelBuffer) {
        return pixelBuffer.getHeight();
    }

    static PixelFormat getPixelFormat(const PixelBuffer &pixelBuffer) {
        return pixelBuffer.getPixelFormat();
    }

    static int getColorChannelCount(const PixelBuffer &pixelBuffer) {
        return pixelBuffer.getColorChannelCount();
    }

    static void *getDataPtr(const PixelBuffer &pixelBuffer) {
        return std::visit([](auto ptr) { return (void *)ptr; }, pixelBuffer.getData());
    }
};

template <> struct ImageBufferTypeTrait<FilmBufferVariantPtr> {
    static int getWidth(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getWidth(filmBufferVariant);
    }

    static int getHeight(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getHeight(filmBufferVariant);
    }

    static PixelFormat getPixelFormat(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getPixelFormat(filmBufferVariant);
    }

    static int getColorChannelCount(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getChannelCount(filmBufferVariant);
    }

    static void *getDataPtr(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getDataPtr(filmBufferVariant);
    }
};

template <typename BufferType> void getWriteDataForChannel(PngWriteData &pngWriteData, const BufferType &buffer) {
    pngWriteData.width = ImageBufferTypeTrait<BufferType>::getWidth(buffer);
    pngWriteData.height = ImageBufferTypeTrait<BufferType>::getHeight(buffer);
    const PixelFormat pixelFormat = ImageBufferTypeTrait<BufferType>::getPixelFormat(buffer);
    const int colorChannelCount = ImageBufferTypeTrait<BufferType>::getColorChannelCount(buffer);

    if (pixelFormat == PixelFormat::UINT8) {
        pngWriteData.pixelBuffer = (unsigned char *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
    } else if (pixelFormat == PixelFormat::FLOAT32) {
        size_t numberOfValues = pngWriteData.width * pngWriteData.height * colorChannelCount;
        pngWriteData.pixelBuffer = (unsigned char *)malloc(numberOfValues);
        pngWriteData.isOwning = true;

        const float *data = (float *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);

        tbb::parallel_for(0UL, numberOfValues, [&pngWriteData, data](size_t i) {
            pngWriteData.pixelBuffer[i] = std::clamp<float>(data[i], 0, 1) * 255;
        });
    } else {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Unsupported PixelFormat '{}'", pixelFormat);
    }

    if (colorChannelCount == 1) {
        pngWriteData.state.info_raw.colortype = LodePNGColorType::LCT_GREY;
    } else {
        pngWriteData.state.info_raw.colortype = LodePNGColorType::LCT_RGB;
    }
}

void writePngFile(const std::string &channelName, const std::filesystem::path &channelPath,
                  PngWriteData &pngWriteData) {
    Logger::info("Writing channel {} to {}..", channelName, channelPath);
    unsigned char *pngFileBuffer;
    size_t pngsize;
    const auto decodeError = lodepng_encode(&pngFileBuffer, &pngsize, pngWriteData.pixelBuffer, pngWriteData.width,
                                            pngWriteData.height, &pngWriteData.state);

    if (decodeError) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Error when encoding PNG image at path {}: {}", channelPath,
                                          lodepng_error_text(decodeError));
    }

    const auto saveFileError =
        lodepng_save_file(pngFileBuffer, pngsize, reinterpret_cast<const char *>(channelPath.u8string().c_str()));
    if (saveFileError) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Error when saving PNG image at path {}: {}", channelPath,
                                          lodepng_error_text(saveFileError));
    }
    lodepng_state_cleanup(&pngWriteData.state);
    free(pngFileBuffer);
}

std::filesystem::path resolveChannelPath(const std::filesystem::path &imagePath, const std::string &channelName) {
    if (channelName == "rgb") {
        return imagePath;
    }

    return imagePath.parent_path() / fmt::format("{}.{}.png", imagePath.stem(), channelName);
}

template <typename ImageType>
void pngWriteImpl(const std::filesystem::path &path, const ImageType &imageType,
                  const ImageFormatWriteOptions &imageFormatWriteOptions) {
    const auto channelViews = imageType.getChannels();
    tbb::parallel_for(0UL, channelViews.size(), [&channelViews, &path](int channelIndex) {
        auto &channelView = channelViews[channelIndex];

        PngWriteData pngWriteData{};
        getWriteDataForChannel(pngWriteData, channelView.channelBuffer);

        const std::filesystem::path channelPath = resolveChannelPath(path, channelView.channelName);
        writePngFile(channelView.channelName, channelPath, pngWriteData);

        if (pngWriteData.isOwning) {
            free(pngWriteData.pixelBuffer);
        }
    });
}

}

void PngImageFormatWriter::write(const std::filesystem::path &path, const Image &image) {
    write(path, image, {});
}

void PngImageFormatWriter::write(const std::filesystem::path &path, const Image &image,
                                 const ImageFormatWriteOptions &imageFormatWriteOptions) {
    internal::pngWriteImpl(path, image, imageFormatWriteOptions);
}

void PngImageFormatWriter::write(const std::filesystem::path &path, const Film &film) {
    write(path, film, {});
}

void PngImageFormatWriter::write(const std::filesystem::path &path, const Film &film,
                                 const ImageFormatWriteOptions &imageFormatWriteOptions) {
    internal::pngWriteImpl(path, film, imageFormatWriteOptions);
}

}