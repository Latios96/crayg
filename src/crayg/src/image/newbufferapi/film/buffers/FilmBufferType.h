#pragma once

#include "utils/EnumFormatter.h"

namespace crayg {

enum class FilmBufferType { UNKNOWN, VALUE, ACCUMULATION };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::FilmBufferType);
