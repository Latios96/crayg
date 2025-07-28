#pragma once

#include "ImageWriter.h"
#include "OpenImageIoImageWriter.h"

namespace crayg {

class OpenExrWriter : public OpenImageIoImageWriter {
  public:
    void writeImage(const Image &image, std::string image_name) override;
    ~OpenExrWriter() override = default;
    void countChannelsAndPixels(const std::vector<Image::ChannelView> &channels, unsigned int &totalValuesCount,
                                int &colorChannelCount) const;
    void collectPixelDataIntoSingleBuffer(unsigned int pixelCount, const std::vector<Image::ChannelView> &channels,
                                          std::vector<std::byte> &pixels) const;
    void writeChannelsToSpec(const std::vector<Image::ChannelView> &channels, OIIO::ImageSpec &spec);
    void writeChannelFormats(OIIO::ImageSpec &spec, const PixelBuffer &channelBuffer) const;
    void writeChannelNames(OIIO::ImageSpec &spec, const Image::ChannelView &channel,
                           const PixelBuffer &channelBuffer) const;
};

}
