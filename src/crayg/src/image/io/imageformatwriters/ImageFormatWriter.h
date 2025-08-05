#pragma once
#include "BaseImageFormatWriteOptions.h"
#include <filesystem>
#include <image/Image.h>
#include <image/film/Film.h>

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
