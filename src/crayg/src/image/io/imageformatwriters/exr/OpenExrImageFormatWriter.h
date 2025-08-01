#pragma once
#include "image/io/imageformatwriters/ImageFormatWriter.h"
#include <ImfCompression.h>
#include <ImfPixelType.h>

namespace crayg {

enum class OpenExrDataWindow { WHOLE_IMAGE, RENDER_REGION, AUTO };

struct OpenExrFormatWriteOptions {
    Imf::Compression compression;
    Imf::PixelType pixelType;
    OpenExrDataWindow openExrDataWindow;
};

class OpenExrImageFormatWriter : public ImageFormatWriter {
  public:
    void write(const std::filesystem::path &path, const Image &image) override;

    void write(const std::filesystem::path &path, const Image &image,
               const ImageFormatWriteOptions &imageFormatWriteOptions) override;

    void write(const std::filesystem::path &path, const Film &film) override;

    void write(const std::filesystem::path &path, const Film &film,
               const ImageFormatWriteOptions &imageFormatWriteOptions) override;
};

}

CRAYG_FMT_ENUM_FORMATTER(crayg::OpenExrDataWindow);
CRAYG_FMT_ENUM_FORMATTER(Imf::Compression);
CRAYG_FMT_ENUM_FORMATTER(Imf::PixelType);