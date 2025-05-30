#pragma once

#include "utils/EnumFormatter.h"

namespace crayg {

enum class IntegratorType { RAYTRACING = 1, DEBUG = 2, AMBIENT_OCCLUSION = 3 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::IntegratorType);
