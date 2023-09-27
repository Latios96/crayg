#include "PngWriter.h"
#include "Logger.h"
#include "image/ColorConversion.h"
#include "utils/Exceptions.h"
#include "utils/ImageChannelPathResolver.h"
#include <OpenImageIO/imageio.h>

namespace crayg {

OIIO::TypeDesc mapPixelFormat(PixelFormat pixelFormat) {
    if (pixelFormat == PixelFormat::FLOAT) {
        return OIIO::TypeDesc::FLOAT;
    } else if (pixelFormat == PixelFormat::UINT8) {
        return OIIO::TypeDesc::UINT8;
    } else {
        CRAYG_LOG_AND_THROW(std::runtime_error("Unsupported pixel format"));
    }
}

void write(std::unique_ptr<OIIO::ImageOutput> &out, PixelBuffer &pixelBuffer) {
    auto pixelFormat = pixelBuffer.getPixelFormat();
    if (pixelFormat == PixelFormat::FLOAT) {
        out->write_image(OIIO::TypeDesc::FLOAT, std::get<float *>(pixelBuffer.getData()));
    } else if (pixelFormat == PixelFormat::UINT8) {
        out->write_image(OIIO::TypeDesc::UINT8, std::get<std::uint8_t *>(pixelBuffer.getData()));
    } else {
        CRAYG_LOG_AND_THROW(std::runtime_error("Unsupported pixel format"));
    }
}

void PngWriter::writeImage(const Image &image, std::string image_name) {
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

        out->open(channelPath, spec);
        write(out, *bufferToWrite);
        out->close();
    }
}

PngWriter::~PngWriter() = default;

}