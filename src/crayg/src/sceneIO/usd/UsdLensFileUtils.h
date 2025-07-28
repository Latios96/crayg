#pragma once

#include "scene/camera/realistic/CameraLens.h"
#include <pxr/usd/usd/prim.h>

namespace crayg {

class UsdLensFileUtils {
  public:
    static void writeEmbeddedLensFile(const CameraLens &cameraLens, pxr::UsdPrim prim);
};

}
