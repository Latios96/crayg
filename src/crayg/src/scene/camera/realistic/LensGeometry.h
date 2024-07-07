#pragma once

#include "utils/EnumUtils.h"

namespace crayg {

enum class LensGeometry { SPHERICAL, PLANAR, CYLINDER_X, CYLINDER_Y, ASPHERICAL };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::LensGeometry);
