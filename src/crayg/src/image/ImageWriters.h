#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEWRITERS_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEWRITERS_H_

#include "Image.h"
#include <string>

namespace crayg {

class ImageWriters {
  public:
    static bool writeImage(const Image &image, const std::string &imagePath);
};

}

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEWRITERS_H_
