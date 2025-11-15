#pragma once

#include "crayg/image/io/imageformatwriters/exr/OpenExrFormatWriteOptions.h"
#include "crayg/image/io/imageformatwriters/png/PngImageFormatWriteOptions.h"

#include <fmt/ostream.h>
#include <ostream>

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

    friend std::ostream &operator<<(std::ostream &os, const ImageFormatWriteOptions &obj);
};

}

template <> struct fmt::formatter<crayg::ImageFormatWriteOptions> : ostream_formatter {};