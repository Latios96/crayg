#pragma once

#include "image/io/imageformatwriters/BaseImageFormatWriteOptions.h"
#include "utils/EnumFormatter.h"
#include <ImfCompression.h>
#include <ImfPixelType.h>
#include <ostream>

namespace crayg {

enum class OpenExrDataWindow { WHOLE_IMAGE, RENDER_REGION, AUTO };

struct OpenExrFormatWriteOptions : BaseImageFormatWriteOptions {
    Imf::Compression compression = Imf::ZIP_COMPRESSION;
    Imf::PixelType pixelType = Imf::HALF;
    OpenExrDataWindow openExrDataWindow = OpenExrDataWindow::WHOLE_IMAGE;

    friend std::ostream &operator<<(std::ostream &os, const OpenExrFormatWriteOptions &options);
    bool operator==(const OpenExrFormatWriteOptions &rhs) const;
    bool operator!=(const OpenExrFormatWriteOptions &rhs) const;
};

}

CRAYG_FMT_ENUM_FORMATTER(crayg::OpenExrDataWindow);

template <> struct fmt::formatter<crayg::OpenExrFormatWriteOptions> : ostream_formatter {};
