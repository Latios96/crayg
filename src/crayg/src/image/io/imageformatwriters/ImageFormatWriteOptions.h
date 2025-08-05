#pragma once

#include "image/io/imageformatwriters/exr/OpenExrFormatWriteOptions.h"
#include "image/io/imageformatwriters/png/PngImageFormatWriteOptions.h"

namespace crayg {

struct ImageFormatWriteOptions {
    PngImageFormatWriteOptions pngImageFormatWriteOptions;
    OpenExrFormatWriteOptions openExrFormatWriteOptions;
};

}