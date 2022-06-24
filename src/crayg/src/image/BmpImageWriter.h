#ifndef CRAYG_BMPIMAGEWRITER_H
#define CRAYG_BMPIMAGEWRITER_H

#include <string>
#include "Image.h"
#include "ImageWriter.h"

namespace crayg {

class BmpImageWriter : public ImageWriter {
 public:
    void writeImage(const Image &image, std::string imageName) override;

    virtual ~BmpImageWriter();
};

}

#endif //CRAYG_BMPIMAGEWRITER_H
