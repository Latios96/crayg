#pragma once

#include "crayg/imaging/CameraLens.h"

namespace crayg {

class CameraLensFixtures {
  public:
    static CameraLens createCanon70_200mm();
    static CameraLens createSchneider30mmAnamorphic();
    static CameraLens createEdmondAsphericLens();
};

}
