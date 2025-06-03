#pragma once

#include "FilmSpec.h"
#include "film/buffers/AccumulationBuffer.h"
#include "film/buffers/BufferBase.h"
#include "film/buffers/BufferVariantConversion.h"
#include "film/buffers/FilmBufferFactory.h"
#include "film/buffers/FilmBufferVariants.h"
#include "film/buffers/ValueBuffer.h"
#include <optional>
#include <tsl/ordered_map.h>

namespace crayg {

struct Film {
    Film(int width, int height);

    Film(const Resolution &resolution);

    void addChannelsFromSpec(const FilmSpec &filmSpec);
    void addChannel(const std::string &name, FilmBufferVariantPtr filmBufferVariantPtr);

    virtual void addSample(const std::string &channelName, const Vector2i &pixelPosition, const Color &value);
    virtual void addSample(const std::string &channelName, const Vector2i &pixelPosition, float value);

    void updateAverages();
    void updateAveragesInBucket(const ImageBucket &imageBucket);

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

        auto accumulationBufferVariantPtr =
            BufferVariantConversion::getAsAccumulationBufferVariantPtr(*bufferVariantPtr);
        if (accumulationBufferVariantPtr) {
            std::visit([&pixelPosition, &value](auto *buf) { buf->add(pixelPosition, value); },
                       *accumulationBufferVariantPtr);
        }

        auto valueBufferVariantPtr = BufferVariantConversion::getAsValueBufferVariantPtr(*bufferVariantPtr);
        if (valueBufferVariantPtr) {
            std::visit([&pixelPosition, &value](auto *buf) { buf->write(pixelPosition, value); },
                       *valueBufferVariantPtr);
        }
    }

    Resolution resolution;
    AccumulationBuffer<float, 3> rgb;
    tsl::ordered_map<std::string, FilmBufferVariantPtr> additionalChannels;
};

// todo convert to image

}
