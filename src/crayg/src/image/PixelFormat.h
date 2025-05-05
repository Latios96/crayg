#pragma once

#include "utils/EnumParser.h"

namespace crayg {

enum class PixelFormat { FLOAT, UINT8 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::PixelFormat);
