#include "PngImageFormatWriter.h"

#include "Logger.h"
#include "image/io/imageformatwriters/ImageBufferTypeTrait.h"

#include <lodepng.h>
#include <tbb/parallel_for.h>

namespace crayg {

namespace internal {

struct PngWriteData {
    unsigned char *pixelBuffer;
    bool isOwning = false;
    LodePNGState state;
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

        tbb::parallel_for(size_t(0), numberOfValues, [&pngWriteData, data](size_t i) {
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
                  const BaseImageFormatWriteOptions &imageFormatWriteOptions) {
    const auto channelViews = imageType.getChannels();
    tbb::parallel_for((size_t)0, channelViews.size(), [&channelViews, &path, &imageType](int channelIndex) {
        auto &channelView = channelViews[channelIndex];

        PngWriteData pngWriteData{};
        lodepng_state_init(&pngWriteData.state);
        getWriteDataForChannel(pngWriteData, channelView.channelBuffer);
        appendImageMetadata(imageType.metadata, pngWriteData);

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
                                 const BaseImageFormatWriteOptions &imageFormatWriteOptions) {
    internal::pngWriteImpl(path, image, imageFormatWriteOptions);
}

void PngImageFormatWriter::write(const std::filesystem::path &path, const Film &film) {
    write(path, film, {});
}

void PngImageFormatWriter::write(const std::filesystem::path &path, const Film &film,
                                 const BaseImageFormatWriteOptions &imageFormatWriteOptions) {
    internal::pngWriteImpl(path, film, imageFormatWriteOptions);
}

}