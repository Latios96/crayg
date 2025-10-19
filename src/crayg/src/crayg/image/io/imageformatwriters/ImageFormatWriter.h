#pragma once
#include "BaseImageFormatWriteOptions.h"
#include "crayg/image/Image.h"
#include "crayg/image/film/Film.h"
#include <filesystem>

namespace crayg {

class ImageFormatWriter {

  public:
    virtual void write(const std::filesystem::path &path, const Image &image) = 0;
    virtual void write(const std::filesystem::path &path, const Image &image,
                       const BaseImageFormatWriteOptions &imageFormatWriteOptions) = 0;
    virtual void write(const std::filesystem::path &path, const Film &film) = 0;
    virtual void write(const std::filesystem::path &path, const Film &film,
                       const BaseImageFormatWriteOptions &imageFormatWriteOptions) = 0;
    virtual ~ImageFormatWriter() = default;
};

}
