#include "Image.h"
#include "utils/Exceptions.h"

namespace crayg {

Image::Image(int width, int height) : rgb(PixelBuffer({width, height}, PixelFormat::FLOAT, 3)) {
}

Image::Image(const Resolution &resolution) : rgb(PixelBuffer(resolution, PixelFormat::FLOAT, 3)) {
}

Image::Image(const Image &image) : rgb(image.rgb), metadata(image.metadata) {
    for (auto &entry : image.additionalChannels) {
        additionalChannels[entry.first] = std::make_unique<PixelBuffer>(*entry.second);
    }
}

int Image::getWidth() const {
    return rgb.getWidth();
}

int Image::getHeight() const {
    return rgb.getHeight();
}

void Image::setValue(const Vector2i &pixelPosition, const Color &color) {
    rgb.setValue(pixelPosition, color);
}

Color Image::getValue(const Vector2i &pixelPosition) const {
    return rgb.getValue(pixelPosition);
}

Resolution Image::getResolution() const {
    return {rgb.getWidth(), rgb.getHeight()};
}

void Image::addAlphaChannel() {
    addChannel("alpha", PixelBuffer::createGreyFloat(getResolution()));
}

bool Image::hasAlphaChannel() const {
    return hasChannel("alpha");
}

PixelBuffer *Image::getAlphaChannel() const {
    return getChannel("alpha");
}

void Image::addDepthChannel() {
    addChannel("depth", PixelBuffer::createGreyFloat(getResolution()));
}

bool Image::hasDepthChannel() const {
    return hasChannel("depth");
}

PixelBuffer *Image::getDepthChannel() const {
    return getChannel("depth");
}

void Image::addChannel(const std::string &name, std::unique_ptr<PixelBuffer> pixelBuffer) {
    if (!hasChannel(name)) {
        additionalChannels[name] = std::move(pixelBuffer);
    }
}

bool Image::hasChannel(const std::string &name) const {
    if (name == "rgb") {
        return true;
    }
    return additionalChannels.find(name) != additionalChannels.end();
}

PixelBuffer *Image::getChannel(const std::string &name) const {
    if (!hasChannel(name)) {
        return nullptr;
    }
    if (name == "rgb") {
        return const_cast<PixelBuffer *>(&rgb);
    }
    return additionalChannels.at(name).get();
}

std::vector<std::string> Image::channelNames() const {
    std::vector<std::string> names;
    names.emplace_back("rgb");
    for (auto &channel : additionalChannels) {
        names.push_back(channel.first);
    }
    return names;
}

std::vector<Image::ChannelView> Image::getChannels() const {
    std::vector<Image::ChannelView> channels;
    channels.emplace_back("rgb", const_cast<PixelBuffer &>(rgb));
    for (auto &channel : additionalChannels) {
        channels.emplace_back(channel.first, *channel.second);
    }
    return channels;
}

void Image::replaceChannel(const std::string &name, std::unique_ptr<PixelBuffer> pixelBuffer) {
    if (name == "rgb") {
        rgb = *pixelBuffer.release();
    } else {
        additionalChannels[name] = std::move(pixelBuffer);
    }
}

bool Image::operator==(const Image &rhs) const {
    const bool metadataMatches = metadata == rhs.metadata;
    const bool rgbMatches = rgb == rhs.rgb;
    bool channelMatch = true;

    for (auto &channel : additionalChannels) {
        if (!rhs.additionalChannels.contains(channel.first)) {
            channelMatch = false;
            break;
        }
    }
    if (channelMatch) {
        for (auto &channel : rhs.additionalChannels) {
            if (!additionalChannels.contains(channel.first)) {
                channelMatch = false;
                break;
            }
        }
    }
    return metadataMatches && rgbMatches && channelMatch;
}

bool Image::operator!=(const Image &rhs) const {
    return !(rhs == *this);
}

ImageSpec Image::getImageSpec() const {
    std::vector<ChannelSpec> channelSpecs({{"rgb", PixelFormat::FLOAT, 3}});

    for (auto &channel : additionalChannels) {
        channelSpecs.emplace_back(channel.first, channel.second->getPixelFormat(),
                                  channel.second->getColorChannelCount());
    }

    return {getResolution(), channelSpecs};
}

void Image::addChannelsFromSpec(const ImageSpec &imageSpec) {
    if (getResolution() != imageSpec.resolution) {
        CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format("Image resolution does not match, was {}, required was {}",
                                                           getResolution(), imageSpec.resolution)));
    }
    for (auto &channel : imageSpec.channels) {
        if (channel.name == "rgb") {
            continue;
        }
        addChannel(channel.name,
                   std::make_unique<PixelBuffer>(getResolution(), channel.pixelFormat, channel.colorChannelCount));
    }
}

Image::ChannelView::ChannelView(const std::string &channelName, PixelBuffer &channelBuffer)
    : channelName(channelName), channelBuffer(channelBuffer) {
}
}