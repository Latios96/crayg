#pragma once

#include "FilmSpec.h"
#include "buffers/FilmAccumulationBuffer.h"
#include "buffers/FilmBufferBase.h"
#include "buffers/FilmBufferFactory.h"
#include "buffers/FilmBufferVariants.h"
#include "buffers/ValueBuffer.h"
#include "image/ImageBucket.h"

#include <optional>
#include <tsl/ordered_map.h>

namespace crayg {

class Image;

struct Film {
    Film(int width, int height);

    Film(const Resolution &resolution);

    void addChannelsFromSpec(const FilmSpec &filmSpec);
    void addChannel(const std::string &name, FilmBufferVariantPtr filmBufferVariantPtr);

    virtual void addSample(const std::string &channelName, const Vector2i &pixelPosition, const Color &value);
    virtual void addSample(const std::string &channelName, const Vector2i &pixelPosition, float value);

    void updateAverages();
    void updateAveragesInBucket(const ImageBucket &imageBucket);

    void toImage(Image &image);

    struct ChannelView {
        ChannelView(const std::string &channelName, FilmBufferVariantPtr channelBuffer);

        std::string channelName;
        FilmBufferVariantPtr channelBuffer;
    };

    std::vector<ChannelView> getChannels() const;
    std::vector<std::string> channelNames() const;
    bool hasChannel(const std::string &name) const;
    std::optional<FilmBufferVariantPtr> getBufferVariantPtrByName(const std::string &name);
    const Resolution &getResolution() const;

    virtual ~Film();

  private:
    template <typename T>
    void addSampleImpl(const std::string &channelName, const Vector2i &pixelPosition, const T &value) {
        if (!hasChannel(channelName)) {
            return;
        }

        if (channelName == "rgb") {
            rgb.add(pixelPosition, value);
            return;
        }

        auto bufferVariantPtr = getBufferVariantPtrByName(channelName);

        auto accumulationBufferVariantPtr = FilmBufferVariants::getAsAccumulationBufferVariantPtr(*bufferVariantPtr);
        if (accumulationBufferVariantPtr) {
            std::visit([&pixelPosition, &value](auto *buf) { buf->add(pixelPosition, value); },
                       *accumulationBufferVariantPtr);
        }

        auto valueBufferVariantPtr = FilmBufferVariants::getAsValueBufferVariantPtr(*bufferVariantPtr);
        if (valueBufferVariantPtr) {
            std::visit([&pixelPosition, &value](auto *buf) { buf->write(pixelPosition, value); },
                       *valueBufferVariantPtr);
        }
    }

    Resolution resolution;
    FilmAccumulationBuffer<float, 3> rgb;
    tsl::ordered_map<std::string, FilmBufferVariantPtr> additionalChannels;
};

// todo convert to image

}
