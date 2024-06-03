#pragma once

#include "ImageWriter.h"
#include <OpenImageIO/imageio.h>

namespace crayg {

class OpenImageIoImageWriter : public ImageWriter {
  public:
    virtual void writeImageMetadata(const Image &image, OIIO::ImageSpec &spec);
    ~OpenImageIoImageWriter() override = default;
};

} // crayg
