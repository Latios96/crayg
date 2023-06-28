#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_POINTINSTANCERFIXTURES_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_POINTINSTANCERFIXTURES_H_

#include "scene/primitives/PointInstancer.h"

namespace crayg {

class PointInstancerFixtures {
  public:
    static void createInstancerWithSingleTriangleProtoType(PointInstancer &pointInstancer);
    static void createInstancerWithSingleSphereProtoType(PointInstancer &pointInstancer);
    static void createInstancerWithSingleSubdivisionSurfaceMeshProtoType(PointInstancer &pointInstancer);

  private:
    static void createInstancerWithSingleProtoType(PointInstancer &pointInstancer,
                                                   std::shared_ptr<SceneObject> &sceneObject);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_TESTS_FIXTURES_POINTINSTANCERFIXTURES_H_
