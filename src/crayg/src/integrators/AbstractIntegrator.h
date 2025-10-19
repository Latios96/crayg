#pragma once

#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/foundation/math/geometry/Ray.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

enum class RayType { CAMERA, DIFFUSE, SPECULAR };

class AbstractIntegrator {
  public:
    explicit AbstractIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector);
    virtual Color integrate(const Ray &ray, int recursionDepth, RayType rayType) = 0;
    virtual ~AbstractIntegrator();

  protected:
    Scene &scene;
    std::shared_ptr<SceneIntersector> sceneIntersector;
};

}
