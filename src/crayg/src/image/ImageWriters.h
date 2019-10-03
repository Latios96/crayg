//
// Created by jan on 03/10/2019.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEWRITERS_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEWRITERS_H_

#include <string>
#include "Image.h"

class ImageWriters {
 public:
    static bool writeImage(const Image &image, const std::string &imagePath);
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEWRITERS_H_
