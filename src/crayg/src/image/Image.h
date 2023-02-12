#ifndef CRAYG_IMAGE_H
#define CRAYG_IMAGE_H

#include <ostream>
#include <tsl/ordered_map.h>
#include <optional>
#include <basics/Resolution.h>
#include "basics/Color.h"
#include "basics/Vector3f.h"
#include "ImageMetadata.h"
#include "PixelPosition.h"
#include "PixelBuffer.h"

namespace crayg {

class Image {

 public:
    Image(int width, int height);
    Image(const Resolution &resolution);
    Image(const Image &image);

    int getWidth() const;
    int getHeight() const;

    void setValue(int x, int y, const Color &color);
    Color getValue(int x, int y) const;

    void addAlphaChannel();
    bool hasAlphaChannel() const;
    std::optional<PixelBuffer *> getAlphaChannel() const;

    void addDepthChannel();
    bool hasDepthChannel() const;
    std::optional<PixelBuffer *> getDepthChannel() const;

    void addChannel(const std::string &name, std::unique_ptr<PixelBuffer> pixelBuffer);
    bool hasChannel(const std::string &name) const;
    std::optional<PixelBuffer *> getChannel(const std::string &name) const;

    void replaceChannel(const std::string &name, std::unique_ptr<PixelBuffer> pixelBuffer);

    struct ChannelView {
        ChannelView(const std::string &channelName, PixelBuffer &channelBuffer);
        std::string channelName;
        PixelBuffer &channelBuffer;
    };

    std::vector<ChannelView> getChannels() const;
    std::vector<std::string_view> channelNames() const;

    bool operator==(const Image &rhs) const;
    bool operator!=(const Image &rhs) const;

    Resolution getResolution() const;
    ImageMetadata metadata;
    PixelBuffer rgb;
 private:
    tsl::ordered_map<std::string, std::unique_ptr<PixelBuffer>> additionalChannels;
};

}
#endif //CRAYG_IMAGE_H
