#pragma once

#include "image/Image.h"
#include <string>

namespace crayg {

class ImageWriters {
  public:
    static bool writeImage(const Image &image, const std::string &imagePath);
};

}
