#pragma once

#include "utils/EnumUtils.h"

namespace crayg {

enum class LensFileFormat { TXT, JSON, EXTENDED_FORMAT };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::LensFileFormat);
