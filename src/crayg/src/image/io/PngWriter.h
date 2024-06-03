#pragma once

#include "ImageWriter.h"
#include "OpenImageIoImageWriter.h"

namespace crayg {

static const int RGB_CHANNEL_COUNT = 3;

class PngWriter : public OpenImageIoImageWriter {
  public:
    void writeImage(const Image &image, std::string image_name) override;
    void writeImageMetadata(const Image &image, OIIO::ImageSpec &spec) override;
    ~PngWriter() override;
};

}
