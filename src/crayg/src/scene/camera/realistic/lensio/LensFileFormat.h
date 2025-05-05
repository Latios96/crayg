#pragma once

#include "utils/EnumParser.h"

namespace crayg {

enum class LensFileFormat { TXT, JSON, EXTENDED_FORMAT, ZEMAX };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::LensFileFormat);
