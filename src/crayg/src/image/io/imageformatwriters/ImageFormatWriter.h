#pragma once
#include <filesystem>
#include <image/Image.h>
#include <image/film/Film.h>

namespace crayg {

struct ImageFormatWriteOptions {};

class ImageFormatWriter {

  public:
    virtual void write(const std::filesystem::path &path, const Image &image) = 0;
    virtual void write(const std::filesystem::path &path, const Image &image,
                       const ImageFormatWriteOptions &imageFormatWriteOptions) = 0;
    virtual void write(const std::filesystem::path &path, const Film &film) = 0;
    virtual void write(const std::filesystem::path &path, const Film &film,
                       const ImageFormatWriteOptions &imageFormatWriteOptions) = 0;
    virtual ~ImageFormatWriter() = default;
};

}
