#include "ImageFormatWriters.h"

#include "Logger.h"
#include "crayg/foundation/tracing/CraygTracing.h"
#include "exr/OpenExrImageFormatWriter.h"
#include "png/PngImageFormatWriter.h"

namespace crayg {

template <typename ImageType>
void writeImpl(const std::filesystem::path &path, const ImageType &image,
               const ImageFormatWriteOptions &imageFormatWriteOptions) {
    CRAYG_TRACE_SCOPE("ImageFormatWriters");
    std::string extension = path.extension().string();
    std::unique_ptr<ImageFormatWriter> imageFormatWriter;

    if (extension == ".png") {
        imageFormatWriter = std::make_unique<PngImageFormatWriter>();
        imageFormatWriter->write(path, image, imageFormatWriteOptions.pngImageFormatWriteOptions);
    } else if (extension == ".exr") {
        imageFormatWriter = std::make_unique<OpenExrImageFormatWriter>();
        imageFormatWriter->write(path, image, imageFormatWriteOptions.openExrFormatWriteOptions);
    } else {
        Logger::error("No ImageWriter found for extension {}", extension);
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("No ImageWriter found for extension {}", extension);
    }

    if (!imageFormatWriter) {
        return;
    }
}

void ImageFormatWriters::write(const std::filesystem::path &path, const Image &image) {
    writeImpl(path, image, {});
}

void ImageFormatWriters::write(const std::filesystem::path &path, const Image &image,
                               const ImageFormatWriteOptions &imageFormatWriteOptions) {
    writeImpl(path, image, imageFormatWriteOptions);
}

void ImageFormatWriters::write(const std::filesystem::path &path, const Film &film) {
    writeImpl(path, film, {});
}

void ImageFormatWriters::write(const std::filesystem::path &path, const Film &film,
                               const ImageFormatWriteOptions &imageFormatWriteOptions) {
    writeImpl(path, film, imageFormatWriteOptions);
}
}