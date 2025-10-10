#pragma once

#include "crayg/foundation/enums/EnumFormatter.h"

namespace crayg {

enum class FilmBufferType { UNKNOWN, VALUE, ACCUMULATION, SUM };

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::FilmBufferType);
