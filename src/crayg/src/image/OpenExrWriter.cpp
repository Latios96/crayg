#include "OpenExrWriter.h"

namespace crayg {

void OpenExrWriter::writeImage(const Image &image, std::string image_name) {
    unsigned int pixelCount = image.getWidth() * image.getHeight();
    unsigned int pixelSize = 0;
    int colorChannelCount = 0;
    const std::vector<Image::ChannelView> &channels = image.getChannels();
    for (auto &channel: channels) {
        PixelBuffer &channelBuffer = channel.channelBuffer;
        unsigned int bytesForChannel =
            channelBuffer.getPixelFormat() == PixelFormat::FLOAT ? sizeof(float) : sizeof(std::uint8_t);
        pixelSize += channelBuffer.getColorChannelCount() * bytesForChannel;
        colorChannelCount += channelBuffer.getColorChannelCount();
    }
    std::vector<std::byte> pixels(pixelSize * pixelCount);
    std::byte *data = pixels.data();
    for (unsigned int pixel = 0; pixel < pixelCount; pixel++) {
        for (auto &channel: channels) {
            int colorChannelCount = channel.channelBuffer.getColorChannelCount();

            const bool isFloat = channel.channelBuffer.getPixelFormat() == PixelFormat::FLOAT;
            const bool isUInt8 = channel.channelBuffer.getPixelFormat() == PixelFormat::UINT8;

            if (isFloat) {
                float *channelData = std::get<float *>(channel.channelBuffer.getData());
                std::size_t amount = sizeof(float) * colorChannelCount;
                std::memcpy(data, channelData + pixel * colorChannelCount, amount);
                data += amount;
            } else if (isUInt8) {
                std::uint8_t *channelData = std::get<std::uint8_t *>(channel.channelBuffer.getData());
                std::size_t amount = sizeof(std::uint8_t) * colorChannelCount;
                std::memcpy(data, channelData + pixel * colorChannelCount, amount);
                data += amount;
            } else {
                throw std::runtime_error("Unsupported pixel format");
            }
        }
    }

    std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create(image_name);
    if (!out)
        return;

    OIIO::ImageSpec spec(image.getWidth(), image.getHeight(), colorChannelCount, OIIO::TypeDesc::FLOAT);

    writeImageMetadata(image, spec);

    int channelIndex = 0;
    spec.channelnames.clear();
    for (auto &channel: channels) {
        PixelBuffer &channelBuffer = channel.channelBuffer;
        for (int i = 0; i < channelBuffer.getColorChannelCount(); i++) {
            if (channelBuffer.getPixelFormat() == PixelFormat::FLOAT) {
                spec.channelformats.push_back(OIIO::TypeFloat);
            } else if (channelBuffer.getPixelFormat() == PixelFormat::UINT8) {
                spec.channelformats.push_back(OIIO::TypeUInt8);
            } else {
                throw std::runtime_error("Unsupported pixel format");
            }
        }
        if (channel.channelName == "rgb") {
            spec.channelnames.emplace_back("R");
            spec.channelnames.emplace_back("G");
            spec.channelnames.emplace_back("B");
            channelIndex += 3;
        } else if (channel.channelName == "alpha") {
            spec.channelnames.emplace_back("A");
            spec.alpha_channel = channelIndex;
            channelIndex++;
        } else if (channel.channelName == "depth") {
            spec.channelnames.emplace_back("Z");
            spec.z_channel = channelIndex;
            channelIndex++;
        } else {
            if (channelBuffer.getColorChannelCount() == 3) {
                spec.channelnames.emplace_back(fmt::format("{}.R", channel.channelName));
                spec.channelnames.emplace_back(fmt::format("{}.G", channel.channelName));
                spec.channelnames.emplace_back(fmt::format("{}.B", channel.channelName));
                channelIndex += 3;
            } else {
                spec.channelnames.emplace_back(channel.channelName);
                channelIndex++;
            }
        }
    }

    out->open(image_name, spec);
    out->write_image(OIIO::TypeDesc::UNKNOWN,
                     pixels.data(),
                     pixelSize);
    out->close();
}
} // crayg