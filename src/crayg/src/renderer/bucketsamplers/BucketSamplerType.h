#pragma once
#include "utils/EnumUtils.h"

namespace crayg {

enum class BucketSamplerType { UNIFORM = 1, ADAPTIVE = 2 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::BucketSamplerType);
