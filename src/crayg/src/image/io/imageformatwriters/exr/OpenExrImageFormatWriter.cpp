#include "OpenExrImageFormatWriter.h"

#include "OpenExrFormatWriteOptions.h"
#include "compatibility/openexr/fmt/ImfCompression_formatter.h"
#include "compatibility/openexr/fmt/ImfPixelType_formatter.h"
#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "image/io/imageformatwriters/ImageBufferTypeTrait.h"
#include "parallel/ParallelLoops.h"

#include <ImfChannelList.h>
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
    Imf::Header header;
    Imf::FrameBuffer frameBuffer;
    std::vector<void *> allocatedTemporaryBuffers;
};

Bounds2di minimalDataWindow(const Image &image) {
    Bounds2di minimalDataWindow;
    for (const auto &coord : AreaIterators::lineByLine(image)) {
        auto color = image.getValue(coord);
        const bool alreadyInCrop = minimalDataWindow.contains(coord);
        if (color > Color::createBlack() && !alreadyInCrop) {
            minimalDataWindow = minimalDataWindow.unionWith(coord);
        }
    }
    return minimalDataWindow;
}

Bounds2di minimalDataWindow(const Film &film) {
    const Resolution resolution = film.getResolution();

    auto bufferVariantPtr = film.getBufferVariantPtrByName("color");
    if (!bufferVariantPtr) {
        return resolution.toBounds();
    }

    auto accumulationBufferPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(*bufferVariantPtr);
    if (!accumulationBufferPtr) {
        return std::visit(
            [&resolution](auto ptr) {
                Bounds2di minimalDataWindow;
                for (const auto &coord : AreaIterators::lineByLine(resolution)) {
                    auto color = ptr->getColor(coord);
                    const bool alreadyInCrop = minimalDataWindow.contains(coord);
                    if (color > Color::createBlack() && !alreadyInCrop) {
                        minimalDataWindow = minimalDataWindow.unionWith(coord);
                    }
                }
                return minimalDataWindow;
            },
            *bufferVariantPtr);
    }

    return std::visit(
        [&resolution](auto ptr) {
            Bounds2di minimalDataWindow;
            for (const auto &coord : AreaIterators::lineByLine(resolution)) {
                auto weight = ptr->getWeight(coord);
                const bool alreadyInCrop = minimalDataWindow.contains(coord);
                if (weight > 0 && !alreadyInCrop) {
                    minimalDataWindow = minimalDataWindow.unionWith(coord);
                }
            }
            return minimalDataWindow;
        },
        *accumulationBufferPtr);
}

Bounds2di getRenderRegion(const Image &image) {
    return image.getImageSpec().regionToRender.value_or(image.getResolution().toBounds());
}

Bounds2di getRenderRegion(const Film &film) {
    return film.getFilmSpec().regionToRender.value_or(film.getResolution().toBounds());
}

template <typename ImageType>
Imath::Box2i determineDataWindow(const OpenExrFormatWriteOptions &openExrFormatWriteOptions,
                                 const ImageType &imageType) {
    if (openExrFormatWriteOptions.openExrDataWindow == OpenExrDataWindow::WHOLE_IMAGE) {
        const Resolution resolution = imageType.getResolution();
        return Imath::Box2i({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1});
    }
    if (openExrFormatWriteOptions.openExrDataWindow == OpenExrDataWindow::RENDER_REGION) {
        const Bounds2di dataWindow = getRenderRegion(imageType);
        return Imath::Box2i({dataWindow.min.x, dataWindow.min.y}, {dataWindow.max.x, dataWindow.max.y});
    }
    if (openExrFormatWriteOptions.openExrDataWindow == OpenExrDataWindow::AUTO) {
        const Bounds2di dataWindow = minimalDataWindow(imageType);
        return Imath::Box2i({dataWindow.min.x, dataWindow.min.y}, {dataWindow.max.x, dataWindow.max.y});
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Unsupported OpenEXR data window mode '{}'",
                                      openExrFormatWriteOptions.openExrDataWindow);
}

bool sourcePixelFormatMatchesTargetPixelFormat(const PixelFormat &pixelFormat, const Imf::PixelType &pixelType) {
    const bool bothAreFloat = pixelType == Imf::FLOAT && pixelFormat == PixelFormat::FLOAT32;
    return bothAreFloat;
}

std::string getExrChannelName(const std::string &channelName, const int channelIndex, const int channelCount) {
    static const char channelIndexToSuffix[] = {'r', 'g', 'b'};

    if (channelCount == 1) {
        return channelName;
    }

    if (channelName == "color" || channelName == "rgb") {
        return std::string() + channelIndexToSuffix[channelIndex];
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
    return static_cast<half>(from) / 255.f;
}

template <typename BufferType>
void getWriteDataForChannel(const OpenExrFormatWriteOptions &openExrFormatWriteOptions,
                            OpenExrWriteData &openExrWriteData, const std::string &channelName,
                            const BufferType &buffer) {
    const int bufferWidth = ImageBufferTypeTrait<BufferType>::getWidth(buffer);
    const PixelFormat pixelFormat = ImageBufferTypeTrait<BufferType>::getPixelFormat(buffer);
    const int colorChannelCount = ImageBufferTypeTrait<BufferType>::getColorChannelCount(buffer);
    auto pixelType = openExrFormatWriteOptions.pixelType;
    const int targetValueSizeInBytes = pixelType == Imf::FLOAT ? 4 : 2;

    char *exrData = nullptr;
    Imath::Box2i &dataWindow = openExrWriteData.header.dataWindow();
    int dataWindowWidth = dataWindow.size().x + 1;
    int dataWindowHeight = dataWindow.size().y + 1;
    int yStrideWidth = 0;
    if (sourcePixelFormatMatchesTargetPixelFormat(pixelFormat, pixelType)) {
        CRAYG_CHECK_OR_THROW(pixelFormat == PixelFormat::FLOAT32,
                             fmt::format("Unsupported pixel format {}", pixelFormat));
        exrData = (char *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
        yStrideWidth = bufferWidth;
    } else {
        size_t bytesToAllocate = dataWindowWidth * dataWindowHeight * colorChannelCount * targetValueSizeInBytes;
        exrData = (char *)malloc(bytesToAllocate);
        openExrWriteData.allocatedTemporaryBuffers.push_back(exrData);
        const int dataWindowOffset = (dataWindow.min.x + dataWindow.min.y * dataWindowWidth) * colorChannelCount;
        yStrideWidth = dataWindowWidth;

        parallelFor2d(dataWindowWidth, dataWindowHeight,
                      [&pixelType, &buffer, dataWindowWidth, colorChannelCount, pixelFormat, exrData, dataWindowOffset,
                       dataWindow, bufferWidth](auto sourcePixel) {
                          for (int channelIndex = 0; channelIndex < colorChannelCount; channelIndex++) {
                              const int sourceIndex = (sourcePixel.x + dataWindow.min.x +
                                                       (sourcePixel.y + dataWindow.min.y) * bufferWidth) *
                                                          colorChannelCount +
                                                      channelIndex;
                              const int targetIndex =
                                  (sourcePixel.x + sourcePixel.y * dataWindowWidth) * colorChannelCount + channelIndex;

                              if (pixelFormat == PixelFormat::FLOAT32 && pixelType == Imf::FLOAT) {
                                  auto *source = (float *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                                  auto *target = (float *)exrData;
                                  target[targetIndex] = convertFloat<float, float>(source[sourceIndex]);
                              } else if (pixelFormat == PixelFormat::UINT8 && pixelType == Imf::FLOAT) {
                                  auto *source = (uint8_t *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                                  auto *target = (float *)exrData;
                                  target[targetIndex] = convertFloat<uint8_t, float>(source[sourceIndex]);
                              } else if (pixelFormat == PixelFormat::FLOAT32 && pixelType == Imf::HALF) {
                                  auto *source = (float *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                                  auto *target = (half *)exrData;
                                  target[targetIndex] = convertFloat<float, half>(source[sourceIndex]);
                              } else if (pixelFormat == PixelFormat::UINT8 && pixelType == Imf::HALF) {
                                  auto *source = (uint8_t *)ImageBufferTypeTrait<BufferType>::getDataPtr(buffer);
                                  auto *target = (half *)exrData;
                                  target[targetIndex] = convertFloat<uint8_t, half>(source[sourceIndex]);
                              } else {
                                  CRAYG_LOG_AND_THROW_RUNTIME_ERROR(
                                      "Unsupported combination of source pixel format '{}' and target pixel type '{}'",
                                      pixelFormat, pixelType);
                              }
                          }
                      });

        exrData -= dataWindowOffset * targetValueSizeInBytes;
    }

    for (int channelIndex = 0; channelIndex < colorChannelCount; channelIndex++) {
        const std::string exrChannelName = getExrChannelName(channelName, channelIndex, colorChannelCount);
        const size_t xStride = colorChannelCount * targetValueSizeInBytes;
        const size_t yStride = colorChannelCount * targetValueSizeInBytes * yStrideWidth;
        openExrWriteData.frameBuffer.insert(exrChannelName, Imf::Slice(openExrFormatWriteOptions.pixelType,
                                                                       exrData + targetValueSizeInBytes * channelIndex,
                                                                       xStride, yStride));
        openExrWriteData.header.channels().insert(exrChannelName, Imf::Channel(openExrFormatWriteOptions.pixelType));
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
                    header.insert(metadataentry.first, Imf::TypedAttribute(value));
                }
            },
            metadataentry.second);
    }
}

template <typename ImageType>
void exrWriteImpl(const std::filesystem::path &path, const ImageType &imageType,
                  const OpenExrFormatWriteOptions &openExrFormatWriteOptions) {

    OpenExrWriteData openExrWriteData{};

    addImageMetadata(openExrWriteData.header, imageType.metadata);

    const Resolution resolution = imageType.getResolution();
    openExrWriteData.header.displayWindow() =
        Imath::Box2i({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1});
    openExrWriteData.header.dataWindow() = determineDataWindow(openExrFormatWriteOptions, imageType);

    openExrWriteData.header.compression() = openExrFormatWriteOptions.compression;

    for (auto &channelView : imageType.getChannels()) {
        getWriteDataForChannel(openExrFormatWriteOptions, openExrWriteData, channelView.channelName,
                               channelView.channelBuffer);
    }
    auto channels = openExrWriteData.header.channels();
    auto dataWindow = openExrWriteData.header.dataWindow();
    Imf::OutputFile file(reinterpret_cast<const char *>(path.u8string().c_str()), openExrWriteData.header);
    file.setFrameBuffer(openExrWriteData.frameBuffer);
    file.writePixels(openExrWriteData.header.dataWindow().size().y + 1);

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

}