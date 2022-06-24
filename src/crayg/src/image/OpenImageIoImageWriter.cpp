#include "OpenImageIoImageWriter.h"
#include <OpenImageIO/imageio.h>

namespace crayg {

void OpenImageIoImageWriter::writeImage(const Image &image, std::string image_name) {
    std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create(image_name);
    if (!out)
        return;

    OIIO::ImageSpec spec(image.getWidth(), image.getHeight(), RGB_CHANNEL_COUNT, OIIO::TypeDesc::FLOAT);
    out->open(image_name, spec);
    out->write_image(OIIO::TypeDesc::FLOAT, image.getValues());
    out->close();
}

OpenImageIoImageWriter::~OpenImageIoImageWriter() = default;

}