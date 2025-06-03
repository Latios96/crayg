#pragma once

#include "utils/EnumFormatter.h"

namespace crayg {

enum class FilmPixelDepth { FLOAT, UINT8 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::FilmPixelDepth);
