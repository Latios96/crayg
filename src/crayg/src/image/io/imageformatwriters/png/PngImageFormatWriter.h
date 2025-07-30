#pragma once
#include "image/io/imageformatwriters/ImageFormatWriter.h"

namespace crayg {

// todo color conversion
// todo tests
// todo voerseeing

class PngImageFormatWriter : public ImageFormatWriter {
  public:
    void write(const std::filesystem::path &path, const Image &image) override;

    void write(const std::filesystem::path &path, const Image &image,
               const ImageFormatWriteOptions &imageFormatWriteOptions) override;

    void write(const std::filesystem::path &path, const Film &film) override;

    void write(const std::filesystem::path &path, const Film &film,
               const ImageFormatWriteOptions &imageFormatWriteOptions) override;
};

}