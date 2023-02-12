#include "OpenImageIoImageWriter.h"
#include <OpenImageIO/imageio.h>

namespace crayg {

void writeImageMetadata(const Image &image, OIIO::ImageSpec &spec) {
    for(auto &metadata : image.metadata){
        if (std::holds_alternative<std::string>(metadata.second)) {
            spec.attribute(metadata.first,std::get<std::string>(metadata.second));
        }else if (std::holds_alternative<int>(metadata.second)) {
            spec.attribute(metadata.first,std::get<int>(metadata.second));
        } else if (std::holds_alternative<float>(metadata.second)) {
            spec.attribute(metadata.first,std::get<float>(metadata.second));
        } else if (std::holds_alternative<std::chrono::seconds>(metadata.second)) {
            spec.attribute(metadata.first,static_cast<unsigned int>(std::get<std::chrono::seconds>(metadata.second).count()));
        }
    }
}

void OpenImageIoImageWriter::writeImage(const Image &image, std::string image_name) {
    std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create(image_name);
    if (!out)
        return;

    OIIO::ImageSpec spec(image.getWidth(), image.getHeight(), RGB_CHANNEL_COUNT, OIIO::TypeDesc::FLOAT);

    writeImageMetadata(image, spec);

    out->open(image_name, spec);
    out->write_image(OIIO::TypeDesc::FLOAT, std::get<float *>(image.rgb.getData()));
    out->close();
}

OpenImageIoImageWriter::~OpenImageIoImageWriter() = default;

}