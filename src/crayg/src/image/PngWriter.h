#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_PNGWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_PNGWRITER_H_

#include "OpenImageIoImageWriter.h"

namespace crayg {

static const int RGB_CHANNEL_COUNT = 3;

class PngWriter : public OpenImageIoImageWriter {
 public:
    void writeImage(const Image &image, std::string image_name) override;
    ~PngWriter() override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_PNGWRITER_H_
