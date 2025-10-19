#pragma once

#include "ImageMetadata.h"
#include "ImageSpec.h"
#include "PixelBuffer.h"
#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/math/geometry/Vector2.h"
#include "crayg/foundation/math/geometry/Vector3f.h"
#include <ostream>
#include <tsl/ordered_map.h>

namespace crayg {

class Image {

  public:
    Image(int width, int height);
    Image(const Resolution &resolution);
    Image(const Image &image);

    int getWidth() const;
    int getHeight() const;

    void setValue(const Vector2i &pixelPosition, const Color &color);
    Color getValue(const Vector2i &pixelPosition) const;

    void addAlphaChannel();
    bool hasAlphaChannel() const;
    PixelBuffer *getAlphaChannel() const;

    void addDepthChannel();
    bool hasDepthChannel() const;
    PixelBuffer *getDepthChannel() const;

    void addChannel(const std::string &name, std::unique_ptr<PixelBuffer> pixelBuffer);
    bool hasChannel(const std::string &name) const;
    PixelBuffer *getChannel(const std::string &name) const;

    void addChannelsFromSpec(const ImageSpec &imageSpec);

    void replaceChannel(const std::string &name, std::unique_ptr<PixelBuffer> pixelBuffer);

    struct ChannelView {
        ChannelView(const std::string &channelName, PixelBuffer &channelBuffer);
        std::string channelName;
        PixelBuffer &channelBuffer;
    };

    std::vector<ChannelView> getChannels() const;
    std::vector<std::string> channelNames() const;

    bool operator==(const Image &rhs) const;
    bool operator!=(const Image &rhs) const;

    Resolution getResolution() const;
    ImageSpec getImageSpec() const;
    ImageMetadata metadata;
    PixelBuffer rgb;

  private:
    tsl::ordered_map<std::string, std::unique_ptr<PixelBuffer>> additionalChannels;
};

}
