#pragma once
#include "utils/EnumFormatter.h"

namespace crayg {

enum class BucketSamplerType { UNIFORM = 1, ADAPTIVE = 2 };

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::BucketSamplerType);
