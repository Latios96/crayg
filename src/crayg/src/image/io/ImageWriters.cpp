#include "ImageWriters.h"
#include "ImageWriter.h"
#include "OpenExrWriter.h"
#include "PngWriter.h"
#include "utils/Exceptions.h"
#include "utils/tracing/CraygTracing.h"
#include <Logger.h>
#include <boost/filesystem.hpp>
#include <fmt/format.h>

namespace crayg {

bool ImageWriters::writeImage(const Image &image, const std::string &imagePath) {
    CRG_TRACE_SCOPE("ImageWriters");
    boost::filesystem::path path(imagePath);
    std::string extension = path.extension().string();
    std::unique_ptr<ImageWriter> imageWriter;

    if (extension == ".png") {
        imageWriter = std::unique_ptr<ImageWriter>(new PngWriter());
    } else if (extension == ".exr") {
        imageWriter = std::unique_ptr<ImageWriter>(new OpenExrWriter());
    } else {
        Logger::error("No ImageWriter found for extension {}", extension);
        CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format("No ImageWriter found for extension {}", extension)));
    }

    if (!imageWriter) {
        return false;
    }

    imageWriter->writeImage(image, imagePath);
    return true;
}

}
