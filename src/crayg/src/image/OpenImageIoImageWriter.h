#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_

#include "ImageWriter.h"

namespace crayg {

static const int RGB_CHANNEL_COUNT = 3;

class OpenImageIoImageWriter : public ImageWriter {
 public:
    void writeImage(const Image &image, std::string image_name) override;

    virtual ~OpenImageIoImageWriter();
};

}

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_
