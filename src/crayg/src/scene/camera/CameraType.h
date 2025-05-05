#pragma once

#include "utils/EnumParser.h"
#include <fmt/format.h>

namespace crayg {

enum class CameraType { PINHOLE = 1, THIN_LENS = 2, REALISTIC = 3 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::CameraType);
