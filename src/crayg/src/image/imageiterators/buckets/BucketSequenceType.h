#pragma once

#include "utils/EnumUtils.h"

namespace crayg {

enum class BucketSequenceType { LINE_BY_LINE = 1, SPIRAL = 2 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::BucketSequenceType);
