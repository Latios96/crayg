#include "OpenImageIoImageWriter.h"

namespace crayg {

void OpenImageIoImageWriter::writeImageMetadata(const Image &image, OIIO::ImageSpec &spec) {
    for (auto &metadata : image.metadata) {
        if (std::holds_alternative<std::string>(metadata.second)) {
            spec.attribute(metadata.first, std::get<std::string>(metadata.second));
        } else if (std::holds_alternative<int>(metadata.second)) {
            spec.attribute(metadata.first, std::get<int>(metadata.second));
        } else if (std::holds_alternative<float>(metadata.second)) {
            spec.attribute(metadata.first, std::get<float>(metadata.second));
        } else if (std::holds_alternative<std::chrono::seconds>(metadata.second)) {
            spec.attribute(metadata.first,
                           static_cast<unsigned int>(std::get<std::chrono::seconds>(metadata.second).count()));
        }
    }
}
} // crayg