#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERATYPE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERATYPE_H_

#include "utils/EnumUtils.h"
#include <fmt/format.h>

namespace crayg {

enum class CameraType { PINE_HOLE = 1, THIN_LENS = 2, REALISTIC = 3, POLYNOMIAL = 4, RAY_LUT = 5 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::CameraType);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERATYPE_H_
