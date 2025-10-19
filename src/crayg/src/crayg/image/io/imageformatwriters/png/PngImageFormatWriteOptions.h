#pragma once
#include "crayg/image/io/imageformatwriters/BaseImageFormatWriteOptions.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

struct PngImageFormatWriteOptions : BaseImageFormatWriteOptions {
    friend std::ostream &operator<<(std::ostream &os, const PngImageFormatWriteOptions &options);
};

}

template <> struct fmt::formatter<crayg::PngImageFormatWriteOptions> : ostream_formatter {};
