#pragma once
#include "crayg/foundation/enums/EnumFormatter.h"

namespace crayg {

enum class TileSamplerType { UNIFORM = 1, ADAPTIVE = 2 };

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::TileSamplerType);
