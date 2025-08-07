#pragma once

#include "utils/EnumFormatter.h"

namespace crayg {

enum class BucketSequenceType { SCANLINE = 1, SPIRAL = 2, MORTON = 3, HILBERT = 4 };

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::BucketSequenceType);
