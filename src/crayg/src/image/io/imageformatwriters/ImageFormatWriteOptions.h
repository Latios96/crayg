#pragma once

#include "image/io/imageformatwriters/exr/OpenExrFormatWriteOptions.h"
#include "image/io/imageformatwriters/png/PngImageFormatWriteOptions.h"

namespace crayg {

struct ImageFormatWriteOptions {
    PngImageFormatWriteOptions pngImageFormatWriteOptions;
    OpenExrFormatWriteOptions openExrFormatWriteOptions;

    bool operator==(const ImageFormatWriteOptions &rhs) const {
        return openExrFormatWriteOptions == rhs.openExrFormatWriteOptions;
    }

    bool operator!=(const ImageFormatWriteOptions &rhs) const {
        return !(rhs == *this);
    }
};

}