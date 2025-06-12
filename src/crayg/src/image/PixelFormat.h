#pragma once

#include "utils/EnumFormatter.h"

namespace crayg {

enum class PixelFormat { FLOAT32, UINT8 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::PixelFormat);
