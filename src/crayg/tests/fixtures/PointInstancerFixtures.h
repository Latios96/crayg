#pragma once

#include "crayg/scene/primitives/PointInstancer.h"

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

}
