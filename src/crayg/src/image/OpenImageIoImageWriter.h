//
// Created by jan on 03/10/2019.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_

static const int RGB_CHANNEL_COUNT = 3;
#include "ImageWriter.h"
class OpenImageIoImageWriter : public ImageWriter{
 public:
    void writeImage(const Image &image, std::string image_name) override;

    virtual ~OpenImageIoImageWriter();
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_OPENIMAGEIOIMAGEWRITER_H_
