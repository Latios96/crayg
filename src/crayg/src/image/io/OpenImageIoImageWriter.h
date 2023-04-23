#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_

#include "ImageWriter.h"
#include <OpenImageIO/imageio.h>

namespace crayg {

class OpenImageIoImageWriter : public ImageWriter {
  public:
    void writeImageMetadata(const Image &image, OIIO::ImageSpec &spec);
    ~OpenImageIoImageWriter() override = default;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_
