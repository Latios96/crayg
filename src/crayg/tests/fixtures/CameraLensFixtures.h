#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_CAMERALENSFIXTURES_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_CAMERALENSFIXTURES_H_

#include "scene/camera/realistic/CameraLens.h"

namespace crayg {

class CameraLensFixtures {
  public:
    static CameraLens createCanon70_200mm();
    static CameraLens createSchneider30mmAnamorphic();
};

} // crayg

#endif // CRAYG_SRC_CRAYG_TESTS_FIXTURES_CAMERALENSFIXTURES_H_
