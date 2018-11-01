//
// Created by Jan Honsbrok on 28.10.18.
//

#ifndef CRAYG_IMAGEWRITERS_H
#define CRAYG_IMAGEWRITERS_H

#include <string>
#include "Image.h"

// todo add virtual destructor
class ImageWriter{
public:
    virtual void writeImage(const Image &image, std::string image_name) = 0;

};

#endif //CRAYG_IMAGEWRITERS_H
