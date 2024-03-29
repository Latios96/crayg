#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSGEOMETRY_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSGEOMETRY_H_

#include "utils/EnumUtils.h"

namespace crayg {

enum LensGeometry { SPHERICAL, PLANAR, CYLINDER_X, CYLINDER_Y };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::LensGeometry);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSGEOMETRY_H_
