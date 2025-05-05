#pragma once

#include "utils/EnumParser.h"
#include <fmt/format.h>

namespace crayg {

enum class IntersectorType { EMBREE = 2 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::IntersectorType);
