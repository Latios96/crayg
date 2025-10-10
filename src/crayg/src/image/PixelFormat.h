#pragma once

#include "crayg/foundation/enums/EnumFormatter.h"

namespace crayg {

enum class PixelFormat { FLOAT32, UINT8 };

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::PixelFormat);
