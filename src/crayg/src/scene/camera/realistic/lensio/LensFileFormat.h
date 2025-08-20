#pragma once

#include "utils/EnumFormatter.h"

namespace crayg {

enum class LensFileFormat { TXT, JSON, EXTENDED_FORMAT, ZEMAX };

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::LensFileFormat);
