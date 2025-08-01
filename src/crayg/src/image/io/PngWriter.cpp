#include "PngWriter.h"
#include "Logger.h"
#include "image/ColorConversion.h"
#include "image/InvalidPixelFormat.h"
#include "utils/Exceptions.h"
#include "utils/ImageChannelPathResolver.h"
#include "utils/tracing/CraygTracing.h"
#include <OpenImageIO/imageio.h>

namespace crayg {

OIIO::TypeDesc mapPixelFormat(PixelFormat pixelFormat) {
    if (pixelFormat == PixelFormat::FLOAT32) {
        return OIIO::TypeDesc::FLOAT;
    } else if (pixelFormat == PixelFormat::UINT8) {
        return OIIO::TypeDesc::UINT8;
    } else {
        CRAYG_LOG_AND_THROW(UnsupportedPixelFormat(pixelFormat));
    }
}

void write(std::unique_ptr<OIIO::ImageOutput> &out, PixelBuffer &pixelBuffer) {
    auto pixelFormat = pixelBuffer.getPixelFormat();

    void *data;
    OIIO::TypeDesc typeDesc;

    if (pixelFormat == PixelFormat::FLOAT32) {
        typeDesc = OIIO::TypeDesc::FLOAT;
        data = std::get<float *>(pixelBuffer.getData());
    } else if (pixelFormat == PixelFormat::UINT8) {
        typeDesc = OIIO::TypeDesc::UINT8;
        data = std::get<uint8_t *>(pixelBuffer.getData());
    } else {
        CRAYG_LOG_AND_THROW(UnsupportedPixelFormat(pixelFormat));
    }
    out->write_image(typeDesc, data);
}

void PngWriter::writeImage(const Image &image, std::string image_name) {
    CRAYG_TRACE_SCOPE("PngWriter");
    ImageChannelPathResolver imageChannelPathResolver;
    for (auto &channel : image.getChannels()) {
        auto channelBuffer = channel.channelBuffer;
        auto channelPath = imageChannelPathResolver.resolve(image_name, channel.channelName);
        Logger::info("Writing channel {} to {}..", channel.channelName, channelPath);
        std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create(channelPath);
        if (!out) {
            return;
        }

        OIIO::ImageSpec spec(image.getWidth(), image.getHeight(), channelBuffer.getColorChannelCount(),
                             mapPixelFormat(channelBuffer.getPixelFormat()));

        writeImageMetadata(image, spec);

        PixelBuffer *bufferToWrite = &channelBuffer;
        std::unique_ptr<PixelBuffer> convertedPixelBuffer;
        if (ColorConversion::channelNeedsLinearToSRgbConversion(channel.channelName)) {
            convertedPixelBuffer = std::make_unique<PixelBuffer>(channelBuffer);
            ColorConversion::linearToSRGB(channelBuffer, *convertedPixelBuffer);
            bufferToWrite = convertedPixelBuffer.get();
        }

        {
            CRAYG_IF_TRACING_ENABLED(MTR_SCOPE("PngWriter", "OpenImageIO::write_image"));
            out->open(channelPath, spec);
            write(out, *bufferToWrite);
            out->close();
        }
    }
}

void PngWriter::writeImageMetadata(const Image &image, OIIO::ImageSpec &spec) {
    CRAYG_TRACE_SCOPE("PngWriter");
    for (auto &metadata : image.metadata) {
        if (std::holds_alternative<std::string>(metadata.second)) {
            spec.attribute(metadata.first, std::get<std::string>(metadata.second));
        } else if (std::holds_alternative<int>(metadata.second)) {
            spec.attribute(metadata.first, fmt::format("{}", std::get<int>(metadata.second)));
        } else if (std::holds_alternative<float>(metadata.second)) {
            spec.attribute(metadata.first, fmt::format("{}", std::get<float>(metadata.second)));
        } else if (std::holds_alternative<std::chrono::seconds>(metadata.second)) {
            spec.attribute(
                metadata.first,
                fmt::format("{}s", static_cast<unsigned int>(std::get<std::chrono::seconds>(metadata.second).count())));
        }
    }
}

PngWriter::~PngWriter() = default;

}