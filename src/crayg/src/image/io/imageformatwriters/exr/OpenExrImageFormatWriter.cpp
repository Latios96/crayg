#include "OpenExrImageFormatWriter.h"

#include "OpenExrFormatWriteOptions.h"
#include "image/io/imageformatwriters/ImageBufferTypeTrait.h"
#include "parallel/ParallelLoops.h"

#include <ImfFrameBuffer.h>
#include <ImfHeader.h>
#include <ImfIntAttribute.h>
#include <ImfOutputFile.h>
#include <ImfStringAttribute.h>
#include <half.h>
#include <tbb/parallel_for.h>

namespace crayg {

namespace internal {

struct OpenExrWriteData {
    Imf::FrameBuffer frameBuffer;
    Imath::Box2i dataWindow;
    std::vector<void *> allocatedTemporaryBuffers;
};

/*
Bounds2di minimalDataWindow(const Image &image) {
    Bounds2di minimalDataWindow;
    for (const auto &coord : ImageIterators::lineByLine(image)) {
        auto color = image.getValue(coord);
        const bool alreadyInCrop = minimalDataWindow.contains(coord);
        if (color > Color::createBlack() && !alreadyInCrop) {
            minimalDataWindow = minimalDataWindow.unionWith(coord);
        }
    }
    return minimalDataWindow;
}

Bounds2di minimalDataWindow(Film &film) {
    Bounds2di minimalDataWindow;

    auto bufferVariantPtr = film.getBufferVariantPtrByName("color");
    if (!bufferVariantPtr) {
        return film.getResolution().toBounds();
    }

    auto accumulationBufferPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(*bufferVariantPtr);
    if (!accumulationBufferPtr) {
        return film.getResolution().toBounds();
    }

    for (const auto &coord : ImageIterators::lineByLine(film)) {
        auto color = image.getValue(coord);
        const bool alreadyInCrop = minimalDataWindow.contains(coord);
        if (color > Color::createBlack() && !alreadyInCrop) {
            minimalDataWindow = minimalDataWindow.unionWith(coord);
        }
    }
    return minimalDataWindow;
}*/

template <typename ImageType>
Imath::Box2i determineDataWindow(const OpenExrFormatWriteOptions &openExrFormatWriteOptions,
                                 const ImageType &imageType) {
    if (openExrFormatWriteOptions.openExrDataWindow == OpenExrDataWindow::WHOLE_IMAGE) {
        const Resolution resolution = imageType.getResolution();
        return Imath::Box2i({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1});
    }
    if (openExrFormatWriteOptions.openExrDataWindow == OpenExrDataWindow::RENDER_REGION) {
        // todo get render region
        const Resolution resolution = imageType.getResolution();
        return Imath::Box2i({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1});
    }
    if (openExrFormatWriteOptions.openExrDataWindow == OpenExrDataWindow::AUTO) {
        // todo get minimal data window
        const Resolution resolution = imageType.getResolution();
        return Imath::Box2i({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1});
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Unsupported OpenEXR data window mode '{}'",
                                      openExrFormatWriteOptions.openExrDataWindow);
}

bool sourcePixelFormatMatchesTargetPixelFormat(const PixelFormat &pixelFormat, const Imf::PixelType &pixelType) {
    const bool bothAreFloat = pixelType == Imf::FLOAT && pixelFormat == PixelFormat::FLOAT32;
    return bothAreFloat;
}

std::string getExrChannelName(const std::string &channelName, const int channelIndex, const int channelCount) {
    static const std::string channelIndexToSuffix = "RGB";

    if (channelCount == 1) {
        return channelName;
    }

    if (channelName == "color" || channelName == "rgb") {
        return &channelIndexToSuffix[channelIndex];
    }

    return fmt::format("{}.{}", channelName, channelIndexToSuffix[channelIndex]);
}

template <typename From, typename To> To convertFloat(From from);

template <> float convertFloat(float from) {
    return from;
}

template <> half convertFloat(float from) {
    return from;
}

template <> float convertFloat(uint8_t from) {
    return static_cast<float>(from) / 255.f;
}

template <> half convertFloat(uint8_t from) {
    return static_cast<float>(from) / 255.f;
}

template <typename BufferType>
void getWriteDataForChannel(const OpenExrFormatWriteOptions &openExrFormatWriteOptions,
                            OpenExrWriteData &openExrWriteData, const std::string &channelName,
                            const BufferType &buffer) {
    const PixelFormat pixelFormat = ImageBufferTypeTrait<BufferType>::getPixelFormat(buffer);
    const int colorChannelCount = ImageBufferTypeTrait<BufferType>::getColorChannelCount(buffer);
    auto pixelType = openExrFormatWriteOptions.pixelType;

    char *exrData = nullptr;
    if (sourcePixelFormatMatchesTargetPixelFormat(pixelFormat, pixelType)) {
        CRAYG_CHECK_OR_THROW(pixelFormat == PixelFormat::FLOAT32,
                             fmt::format("Unsupported pixel format {}", pixelFormat));
        const int byteSize = 4;
        exrData = (char *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
        exrData += (openExrWriteData.dataWindow.min.x +
                    openExrWriteData.dataWindow.min.y * openExrWriteData.dataWindow.size().x) *
                   colorChannelCount * byteSize;
    } else {
        const int byteSize = pixelType == Imf::FLOAT ? 4 : 2;
        size_t bytesToAllocate = openExrWriteData.dataWindow.size().x * openExrWriteData.dataWindow.size().y * byteSize;
        exrData = (char *)malloc(bytesToAllocate);

        parallelFor2d(5, 3, [&pixelType, &buffer, &openExrWriteData, colorChannelCount, pixelFormat](auto pixelIndex) {
            for (int channelIndex = 0; channelIndex < colorChannelCount; channelIndex++) {
                const int sourceIndex = // todo respect data window offset
                    (pixelIndex.x + pixelIndex.y * openExrWriteData.dataWindow.size().x) * colorChannelCount +
                    channelIndex;
                const int targetIndex =
                    (pixelIndex.x + pixelIndex.y * openExrWriteData.dataWindow.size().x) * colorChannelCount +
                    channelIndex;

                if (pixelFormat == PixelFormat::FLOAT32 && pixelType == Imf::FLOAT) {
                    auto *source = (float *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                    auto *target = (float *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                    target[targetIndex] = convertFloat<float, float>(source[sourceIndex]);
                } else if (pixelFormat == PixelFormat::UINT8 && pixelType == Imf::FLOAT) {
                    auto *source = (uint8_t *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                    auto *target = (float *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                    target[targetIndex] = convertFloat<float, float>(source[sourceIndex]);
                } else if (pixelFormat == PixelFormat::FLOAT32 && pixelType == Imf::HALF) {
                    auto *source = (float *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                    auto *target = (half *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                    target[targetIndex] = convertFloat<float, float>(source[sourceIndex]);
                } else if (pixelFormat == PixelFormat::UINT8 && pixelType == Imf::HALF) {
                    auto *source = (uint8_t *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                    auto *target = (half *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                    target[targetIndex] = convertFloat<float, float>(source[sourceIndex]);
                } else {
                    CRAYG_LOG_AND_THROW_RUNTIME_ERROR(
                        "Unsupported combination of source pixel format '{}' and target pixel type '{}'", pixelFormat,
                        pixelType);
                }
            }
        });
    }

    for (int channelIndex = 0; channelIndex < colorChannelCount; channelIndex++) {
        const std::string exrChannelName = getExrChannelName(channelName, channelIndex, colorChannelCount);
        const size_t xStride = colorChannelCount;
        const size_t yStride = colorChannelCount * openExrWriteData.dataWindow.size().x;

        openExrWriteData.frameBuffer.insert(exrChannelName,
                                            Imf::Slice(openExrFormatWriteOptions.pixelType, exrData, xStride, yStride));
    }
}

void addImageMetadata(Imf::Header &header, const ImageMetadata &imageMetadata) {
    for (auto &metadataentry : imageMetadata) {
        std::visit(
            [&header, &metadataentry](auto value) {
                if constexpr (std::is_same<decltype(value), std::chrono::seconds>::value) {
                    header.insert(metadataentry.first,
                                  Imf::TypedAttribute(
                                      static_cast<int>(std::get<std::chrono::seconds>(metadataentry.second).count())));
                } else {
                    header[metadataentry.first] = Imf::TypedAttribute(value);
                }
            },
            metadataentry.second);
    }
}

template <typename ImageType>
void exrWriteImpl(const std::filesystem::path &path, const ImageType &imageType,
                  const OpenExrFormatWriteOptions &openExrFormatWriteOptions) {

    OpenExrWriteData openExrWriteData{};
    Imf::Header header;

    addImageMetadata(header, imageType.metadata);

    const Resolution resolution = imageType.getResolution();
    header.displayWindow() = Imath::Box2i({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1});
    header.dataWindow() = determineDataWindow(openExrFormatWriteOptions, imageType);

    for (auto &channelView : imageType.getChannels()) {

        getWriteDataForChannel(openExrFormatWriteOptions, openExrWriteData, channelView.channelName,
                               channelView.channelBuffer);
    }

    Imf::OutputFile file(reinterpret_cast<const char *>(path.u8string().c_str()), header);
    file.setFrameBuffer(openExrWriteData.frameBuffer);
    file.writePixels(header.dataWindow().size().y);

    for (auto ptr : openExrWriteData.allocatedTemporaryBuffers) {
        free(ptr);
    }
}

}

void OpenExrImageFormatWriter::write(const std::filesystem::path &path, const Image &image) {
    write(path, image, {});
}

void OpenExrImageFormatWriter::write(const std::filesystem::path &path, const Image &image,
                                     const BaseImageFormatWriteOptions &imageFormatWriteOptions) {
    internal::exrWriteImpl(path, image, reinterpret_cast<const OpenExrFormatWriteOptions &>(imageFormatWriteOptions));
}

void OpenExrImageFormatWriter::write(const std::filesystem::path &path, const Film &film) {
    write(path, film, {});
}

void OpenExrImageFormatWriter::write(const std::filesystem::path &path, const Film &film,
                                     const BaseImageFormatWriteOptions &imageFormatWriteOptions) {
    internal::exrWriteImpl(path, film, reinterpret_cast<const OpenExrFormatWriteOptions &>(imageFormatWriteOptions));
}

// todo write exr asserter (open exr file, can do assertions like hasChannel(name, type) etc

}