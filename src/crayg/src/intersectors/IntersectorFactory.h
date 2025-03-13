#pragma once

#include "IntersectorType.h"
#include "SceneIntersector.h"

namespace crayg {

class IntersectorFactory {
  public:
    static std::shared_ptr<SceneIntersector> createSceneIntersector(const IntersectorType &intersectorType,
                                                                    Scene &scene);

    static std::shared_ptr<SceneIntersector> createEmbreeBvh(Scene &scene);
};

} // crayg
