#pragma once

#include "image/io/imageformatwriters/BaseImageFormatWriteOptions.h"
#include "utils/EnumFormatter.h"
#include <ImfCompression.h>
#include <ImfPixelType.h>

namespace crayg {

enum class OpenExrDataWindow { WHOLE_IMAGE, RENDER_REGION, AUTO };

struct OpenExrFormatWriteOptions : BaseImageFormatWriteOptions {
    Imf::Compression compression;
    Imf::PixelType pixelType;
    OpenExrDataWindow openExrDataWindow;
};

}

CRAYG_FMT_ENUM_FORMATTER(crayg::OpenExrDataWindow);