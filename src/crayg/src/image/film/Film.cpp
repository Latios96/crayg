#include "Film.h"
#include "crayg/foundation/enums/ValueMapper.h"
#include "image/Image.h"

namespace crayg {
Film::Film(int width, int height)
    : color(new Color3fAccumulationBuffer(width, height)),
      filmSpec(FilmSpecBuilder(Resolution(width, height)).finish()) {
}

Film::Film(const Resolution &resolution)
    : color(new Color3fAccumulationBuffer(resolution)), filmSpec(FilmSpecBuilder(resolution).finish()) {
}

Film::Film(const FilmSpec &filmSpec) {
    addChannelsFromSpec(filmSpec);
}

void Film::addChannelsFromSpec(const FilmSpec &filmSpec) {
    const bool isEmpty = this->filmSpec.resolution == Resolution();
    if ((!isEmpty) && this->filmSpec.resolution != filmSpec.resolution) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Image resolution does not match, was {}, required was {}",
                                          this->filmSpec.resolution, filmSpec.resolution);
    }
    for (auto &channelSpec : filmSpec.channels) {
        if (channelSpec.name == "color") {
            color = FilmBufferFactory::createFilmBuffer(filmSpec.resolution, channelSpec.bufferType,
                                                        channelSpec.pixelFormat, channelSpec.channelCount);
        }
        addChannel(channelSpec.name,
                   FilmBufferFactory::createFilmBuffer(filmSpec.resolution, channelSpec.bufferType,
                                                       channelSpec.pixelFormat, channelSpec.channelCount));
    }
    this->filmSpec = filmSpec;
}

void Film::addChannel(const std::string &name, FilmBufferVariantPtr filmBufferVariantPtr) {
    const bool isEmpty = this->filmSpec.resolution == Resolution();
    std::visit(
        [this, isEmpty](auto buf) {
            if ((!isEmpty) && this->filmSpec.resolution != Resolution(buf->width, buf->height)) {
                CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Resolutions don't match, expected {}, was {}x{}",
                                                  this->filmSpec.resolution, buf->width, buf->height);
            }
        },
        filmBufferVariantPtr);

    if (!hasChannel(name)) {
        additionalChannels[name] = filmBufferVariantPtr;
    }
}

void Film::addSample(const std::string &channelName, const Vector2i &pixelPosition, const Color &value) {
    addSampleImpl(channelName, pixelPosition, value);
}

void Film::addSample(const std::string &channelName, const Vector2i &pixelPosition, float value) {
    addSampleImpl(channelName, pixelPosition, value);
}

void Film::updateAverages() {
    auto accumulationBufferVariantPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(color);
    if (accumulationBufferVariantPtr) {
        std::visit([](auto *buf) { buf->updateAverages(); }, *accumulationBufferVariantPtr);
    }
    for (auto &channel : additionalChannels) {
        auto accumulationBufferVariantPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(channel.second);
        if (accumulationBufferVariantPtr) {
            std::visit([](auto *buf) { buf->updateAverages(); }, *accumulationBufferVariantPtr);
        }
    }
}

void Film::updateAveragesInTile(const Tile &tile) {
    auto accumulationBufferVariantPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(color);
    if (accumulationBufferVariantPtr) {
        std::visit([&tile](auto *buf) { buf->updateAveragesInTile(tile); }, *accumulationBufferVariantPtr);
    }
    for (auto &channel : additionalChannels) {
        auto accumulationBufferVariantPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(channel.second);
        if (accumulationBufferVariantPtr) {
            std::visit([&tile](auto *buf) { buf->updateAveragesInTile(tile); }, *accumulationBufferVariantPtr);
        }
    }
}

std::vector<Film::ChannelView> Film::getChannels() const {
    std::vector<ChannelView> channels;
    channels.emplace_back("color", color);
    for (auto &channel : additionalChannels) {
        channels.emplace_back(channel.first, channel.second);
    }
    return channels;
}

std::vector<std::string> Film::channelNames() const {
    std::vector<std::string> names;
    names.emplace_back("color");
    for (auto &channel : additionalChannels) {
        names.push_back(channel.first);
    }
    return names;
}

bool Film::hasChannel(const std::string &name) const {
    if (name == "color") {
        return true;
    }
    return additionalChannels.find(name) != additionalChannels.end();
}

std::optional<FilmBufferVariantPtr> Film::getBufferVariantPtrByName(const std::string &name) const {
    if (!hasChannel(name)) {
        return std::nullopt;
    }

    if (name == "color") {
        return color;
    }

    return additionalChannels.at(name);
}

FilmSpec Film::getFilmSpec() const {
    return filmSpec;
}

Resolution Film::getResolution() const {
    return FilmBufferVariants::getResolution(color);
}

Film::~Film() {
    std::visit([](auto *buf) { delete buf; }, color);
    for (auto &channel : additionalChannels) {
        std::visit([](auto *buf) { delete buf; }, channel.second);
    }
}

Film::ChannelView::ChannelView(const std::string &channelName, FilmBufferVariantPtr channelBuffer)
    : channelName(channelName), channelBuffer(channelBuffer) {
}

const auto pixelFormatAndByteCount =
    ValueMapper<PixelFormat, int>({{PixelFormat::FLOAT32, 4}, {PixelFormat::UINT8, 1}});

void Film::toImage(Image &image) const {
    for (auto channel : getChannels()) {
        const std::string mappedChannelName = channel.channelName == "color" ? "rgb" : channel.channelName;
        const PixelFormat pixelFormat = FilmBufferVariants::getPixelFormat(channel.channelBuffer);
        const int channelCount = FilmBufferVariants::getChannelCount(channel.channelBuffer);
        const void *channelDataPtr = FilmBufferVariants::getDataPtr(channel.channelBuffer);

        const int bytesPerPixel = *pixelFormatAndByteCount.mapFromLeft(pixelFormat);

        if (mappedChannelName != "rgb") {
            image.addChannel(mappedChannelName,
                             std::make_unique<PixelBuffer>(filmSpec.resolution, pixelFormat, channelCount));
        }

        auto imageChannel = image.getChannel(mappedChannelName);
        void *dstPtr = std::visit([](auto data) { return (void *)data; }, imageChannel->getData());
        std::memcpy(dstPtr, channelDataPtr,
                    filmSpec.resolution.getWidth() * filmSpec.resolution.getHeight() * bytesPerPixel * channelCount);
    }
}

void Film::updateAveragesForChannel(const std::string &channelName) {
    auto buffer = getBufferVariantPtrByName(channelName);
    if (!buffer) {
        return;
    }
    auto accumulationBuffer = FilmBufferVariants::getAsAccumulationBufferVariantPtr(*buffer);
    if (!accumulationBuffer) {
        return;
    }
    std::visit([](auto *buf) { buf->updateAverages(); }, *accumulationBuffer);
}

void Film::updateAveragesForChannelInTile(const Tile &tile, const std::string &channelName) {
    auto buffer = getBufferVariantPtrByName(channelName);
    if (!buffer) {
        return;
    }
    auto accumulationBuffer = FilmBufferVariants::getAsAccumulationBufferVariantPtr(*buffer);
    if (!accumulationBuffer) {
        return;
    }
    std::visit([&tile](auto *buf) { buf->updateAveragesInTile(tile); }, *accumulationBuffer);
}

}