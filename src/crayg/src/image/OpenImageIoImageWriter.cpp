//
// Created by jan on 03/10/2019.
//

#include "OpenImageIoImageWriter.h"
#include <OpenImageIO/imageio.h>
using namespace OIIO;

void OpenImageIoImageWriter::writeImage(const Image &image, std::string image_name) {
    std::unique_ptr<ImageOutput> out = ImageOutput::create(image_name);
    if (!out)
        return;

    ImageSpec spec(image.getWidth(), image.getHeight(), RGB_CHANNEL_COUNT, TypeDesc::FLOAT);
    out->open(image_name, spec);
    out->write_image(TypeDesc::FLOAT, image.getValues());
    out->close();
}

OpenImageIoImageWriter::~OpenImageIoImageWriter() = default;
