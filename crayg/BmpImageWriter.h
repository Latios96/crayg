//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_BMPIMAGEWRITER_H
#define CRAYG_BMPIMAGEWRITER_H


#include <string>
#include "Image.h"

class BmpImageWriter{
public:
    void write_image(const Image &image, const std::string image_name);

};


#endif //CRAYG_BMPIMAGEWRITER_H
