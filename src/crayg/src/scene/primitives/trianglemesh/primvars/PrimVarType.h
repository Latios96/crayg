#pragma once

#include "utils/EnumParser.h"

namespace crayg {

enum class PrimVarType { PER_FACE, PER_POINT, PER_VERTEX };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::PrimVarType);
