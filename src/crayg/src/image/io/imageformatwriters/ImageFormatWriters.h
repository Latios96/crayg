#pragma once
#include "ImageFormatWriter.h"
#include <filesystem>

namespace crayg {

class ImageFormatWriters {
  public:
    static void write(const std::filesystem::path &path, const Image &image);
    static void write(const std::filesystem::path &path, const Image &image,
                      const ImageFormatWriteOptions &imageFormatWriteOptions);
    static void write(const std::filesystem::path &path, const Film &film);
    static void write(const std::filesystem::path &path, const Film &film,
                      const ImageFormatWriteOptions &imageFormatWriteOptions);
};

}
