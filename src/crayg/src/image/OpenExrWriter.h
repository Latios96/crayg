#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_OPENEXRWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_OPENEXRWRITER_H_

#include "ImageWriter.h"
#include "OpenImageIoImageWriter.h"

namespace crayg {

class OpenExrWriter : public OpenImageIoImageWriter {
 public:
    void writeImage(const Image &image, std::string image_name) override;
    ~OpenExrWriter() override = default;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_OPENEXRWRITER_H_
