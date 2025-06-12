#pragma once

#include "scene/camera/realistic/CameraLens.h"

namespace crayg {

class CameraLensFixtures {
  public:
    static CameraLens createCanon70_200mm();
    static CameraLens createSchneider30mmAnamorphic();
    static CameraLens createEdmondAsphericLens();
};

} // crayg
