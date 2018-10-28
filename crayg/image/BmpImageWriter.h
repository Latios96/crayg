//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_BMPIMAGEWRITER_H
#define CRAYG_BMPIMAGEWRITER_H


#include <string>
#include "Image.h"
#include "ImageWriter.h"

class BmpImageWriter : public ImageWriter{
public:
    void writeImage(const Image &image, const std::string image_name) override;

};


#endif //CRAYG_BMPIMAGEWRITER_H
