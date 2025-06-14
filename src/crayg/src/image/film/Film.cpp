#include "Film.h"
#include "image/Image.h"
#include "utils/ValueMapper.h"

namespace crayg {
Film::Film(int width, int height) : rgb(width, height), filmSpec(FilmSpecBuilder(Resolution(width, height)).finish()) {
}

Film::Film(const Resolution &resolution) : rgb(resolution), filmSpec(FilmSpecBuilder(resolution).finish()) {
}

void Film::addChannelsFromSpec(const FilmSpec &filmSpec) {
    if (this->filmSpec.resolution != filmSpec.resolution) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Image resolution does not match, was {}, required was {}",
                                          this->filmSpec.resolution, filmSpec.resolution);
    }
    for (auto &channelSpec : filmSpec.channels) {
        if (channelSpec.name == "rgb") {
            continue;
        }
        addChannel(channelSpec.name,
                   FilmBufferFactory::createFilmBuffer(filmSpec.resolution, channelSpec.bufferType,
                                                       channelSpec.pixelFormat, channelSpec.channelCount));
    }
    this->filmSpec = filmSpec;
}

void Film::addChannel(const std::string &name, FilmBufferVariantPtr filmBufferVariantPtr) {
    std::visit(
        [this](auto buf) {
            if (this->filmSpec.resolution != Resolution(buf->width, buf->height)) {
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
    rgb.updateAverages();
    for (auto &channel : additionalChannels) {
        auto accumulationBufferVariantPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(channel.second);
        if (accumulationBufferVariantPtr) {
            std::visit([](auto *buf) { buf->updateAverages(); }, *accumulationBufferVariantPtr);
        }
    }
}

void Film::updateAveragesInBucket(const ImageBucket &imageBucket) {
    rgb.updateAveragesInBucket(imageBucket);
    for (auto &channel : additionalChannels) {
        auto accumulationBufferVariantPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(channel.second);
        if (accumulationBufferVariantPtr) {
            std::visit([&imageBucket](auto *buf) { buf->updateAveragesInBucket(imageBucket); },
                       *accumulationBufferVariantPtr);
        }
    }
}

std::vector<Film::ChannelView> Film::getChannels() const {
    std::vector<ChannelView> channels;
    channels.emplace_back("rgb", FilmBufferVariantPtr(const_cast<Color3fAccumulationBuffer *>(&rgb)));
    for (auto &channel : additionalChannels) {
        channels.emplace_back(channel.first, channel.second);
    }
    return channels;
}

std::vector<std::string> Film::channelNames() const {
    std::vector<std::string> names;
    names.emplace_back("rgb");
    for (auto &channel : additionalChannels) {
        names.push_back(channel.first);
    }
    return names;
}

bool Film::hasChannel(const std::string &name) const {
    if (name == "rgb") {
        return true;
    }
    return additionalChannels.find(name) != additionalChannels.end();
}

std::optional<FilmBufferVariantPtr> Film::getBufferVariantPtrByName(const std::string &name) { // todo test
    if (!hasChannel(name)) {
        return std::nullopt;
    }

    if (name == "rgb") {
        return &rgb;
    }

    return additionalChannels.at(name);
}

FilmSpec Film::getFilmSpec() const {
    return filmSpec;
}

ImageMetadata Film::getMetadata() const {
    return metadata;
}

Film::~Film() {
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
        const PixelFormat pixelFormat = FilmBufferVariants::getPixelFormat(channel.channelBuffer);
        const int channelCount = FilmBufferVariants::getChannelCount(channel.channelBuffer);
        const void *channelDataPtr = FilmBufferVariants::getDataPtr(channel.channelBuffer);

        const int bytesPerPixel = *pixelFormatAndByteCount.mapFromLeft(pixelFormat);

        if (channel.channelName != "rgb") {
            image.addChannel(channel.channelName,
                             std::make_unique<PixelBuffer>(filmSpec.resolution, pixelFormat, channelCount));
        }

        auto imageChannel = image.getChannel(channel.channelName);
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

void Film::updateAveragesForChannelInBucket(const ImageBucket &imageBucket, const std::string &channelName) {
    auto buffer = getBufferVariantPtrByName(channelName);
    if (!buffer) {
        return;
    }
    auto accumulationBuffer = FilmBufferVariants::getAsAccumulationBufferVariantPtr(*buffer);
    if (!accumulationBuffer) {
        return;
    }
    std::visit([&imageBucket](auto *buf) { buf->updateAveragesInBucket(imageBucket); }, *accumulationBuffer);
}

}