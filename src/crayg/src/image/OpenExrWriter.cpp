#include "OpenExrWriter.h"

namespace crayg {

void OpenExrWriter::writeImage(const Image &image, std::string image_name) {
    unsigned int pixelCountPerChannel = image.getWidth() * image.getHeight();

    unsigned int totalValuesCount = 0;
    int colorChannelCount = 0;
    const std::vector<Image::ChannelView> &channels = image.getChannels();
    countChannelsAndPixels(channels, totalValuesCount, colorChannelCount);

    std::vector<std::byte> pixels(totalValuesCount * pixelCountPerChannel);
    collectPixelDataIntoSingleBuffer(pixelCountPerChannel, channels, pixels);

    std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create(image_name);
    if (!out)
        return;

    OIIO::ImageSpec spec(image.getWidth(), image.getHeight(), colorChannelCount, OIIO::TypeDesc::FLOAT);

    writeImageMetadata(image, spec);
    writeChannelsToSpec(channels, spec);

    out->open(image_name, spec);
    out->write_image(OIIO::TypeDesc::UNKNOWN,
                     pixels.data(),
                     totalValuesCount);
    out->close();
}

void OpenExrWriter::countChannelsAndPixels(const std::vector<Image::ChannelView> &channels,
                                           unsigned int &totalValuesCount,
                                           int &colorChannelCount) const {
    for (auto &channel: channels) {
        PixelBuffer &channelBuffer = channel.channelBuffer;
        unsigned int bytesForChannel =
            channelBuffer.getPixelFormat() == PixelFormat::FLOAT ? sizeof(float) : sizeof(uint8_t);
        totalValuesCount += channelBuffer.getColorChannelCount() * bytesForChannel;
        colorChannelCount += channelBuffer.getColorChannelCount();
    }
}

void OpenExrWriter::collectPixelDataIntoSingleBuffer(unsigned int pixelCount,
                                                     const std::vector<Image::ChannelView> &channels,
                                                     std::vector<std::byte> &pixels) const {
    std::byte *data = pixels.data();
    for (unsigned int pixel = 0; pixel < pixelCount; pixel++) {
        for (auto &channel: channels) {
            int colorChannelCount = channel.channelBuffer.getColorChannelCount();

            const bool isFloat = channel.channelBuffer.getPixelFormat() == PixelFormat::FLOAT;
            const bool isUInt8 = channel.channelBuffer.getPixelFormat() == PixelFormat::UINT8;

            if (isFloat) {
                float *channelData = std::get<float *>(channel.channelBuffer.getData());
                size_t amount = sizeof(float) * colorChannelCount;
                memcpy(data, channelData + pixel * colorChannelCount, amount);
                data += amount;
            } else if (isUInt8) {
                uint8_t *channelData = std::get<uint8_t *>(channel.channelBuffer.getData());
                size_t amount = sizeof(uint8_t) * colorChannelCount;
                memcpy(data, channelData + pixel * colorChannelCount, amount);
                data += amount;
            } else {
                throw std::runtime_error("Unsupported pixel format");
            }
        }
    }
}

void OpenExrWriter::writeChannelsToSpec(const std::vector<Image::ChannelView> &channels,
                                        OIIO::ImageSpec &spec) {
    spec.channelnames.clear();
    for (auto &channel: channels) {
        PixelBuffer &channelBuffer = channel.channelBuffer;
        writeChannelFormats(spec, channelBuffer);
        writeChannelNames(spec, channel, channelBuffer);
    }
}

void OpenExrWriter::writeChannelNames(OIIO::ImageSpec &spec,
                                      const Image::ChannelView &channel,
                                      const PixelBuffer &channelBuffer) const {
    int channelIndex = 0;
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

void OpenExrWriter::writeChannelFormats(OIIO::ImageSpec &spec, const PixelBuffer &channelBuffer) const {
    for (int i = 0; i < channelBuffer.getColorChannelCount(); i++) {
        if (channelBuffer.getPixelFormat() == PixelFormat::FLOAT) {
            spec.channelformats.push_back(OIIO::TypeFloat);
        } else if (channelBuffer.getPixelFormat() == PixelFormat::UINT8) {
            spec.channelformats.push_back(OIIO::TypeUInt8);
        } else {
            throw std::runtime_error("Unsupported pixel format");
        }
    }
}

} // crayg