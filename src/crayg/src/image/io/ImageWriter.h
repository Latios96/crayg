#ifndef CRAYG_IMAGEWRITERS_H
#define CRAYG_IMAGEWRITERS_H

#include "image/Image.h"
#include <string>

namespace crayg {

class ImageWriter {
  public:
    virtual void writeImage(const Image &image, std::string image_name) = 0;

    virtual ~ImageWriter() = default;
};

}

#endif // CRAYG_IMAGEWRITERS_H
