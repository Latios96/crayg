#pragma once

#include "utils/EnumFormatter.h"

namespace crayg {

enum class FilmBufferType { UNKNOWN, VALUE, ACCUMULATION, SUM };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::FilmBufferType);
