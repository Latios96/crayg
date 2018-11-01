//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_BMPIMAGEWRITER_H
#define CRAYG_BMPIMAGEWRITER_H


#include <string>
#include "Image.h"
#include "ImageWriter.h"
// todo add virtual destructor
class BmpImageWriter : public ImageWriter{
public:
    void writeImage(const Image &image, const std::string imageName) override;

};


#endif //CRAYG_BMPIMAGEWRITER_H
