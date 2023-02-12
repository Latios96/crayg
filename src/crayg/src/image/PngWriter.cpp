#include "PngWriter.h"
#include <OpenImageIO/imageio.h>

namespace crayg {

void PngWriter::writeImage(const Image &image, std::string image_name) {
    std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create(image_name);
    if (!out)
        return;

    OIIO::ImageSpec spec(image.getWidth(), image.getHeight(), RGB_CHANNEL_COUNT, OIIO::TypeDesc::FLOAT);

    writeImageMetadata(image, spec);

    out->open(image_name, spec);
    out->write_image(OIIO::TypeDesc::FLOAT, std::get<float *>(image.rgb.getData()));
    out->close();
}

PngWriter::~PngWriter() = default;

}