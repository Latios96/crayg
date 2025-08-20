#pragma once

#include "utils/EnumFormatter.h"
#include <fmt/format.h>

namespace crayg {

enum class IntersectorType { EMBREE = 2 };

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::IntersectorType);
