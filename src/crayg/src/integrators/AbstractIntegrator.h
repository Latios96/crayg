#pragma once

#include "IntegratorContext.h"
#include "basics/Color.h"
#include "basics/Ray.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

class AbstractIntegrator {
  public:
    explicit AbstractIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector);
    virtual Color integrate(const Ray &ray, int recursionDepth) = 0;
    virtual ~AbstractIntegrator();

  protected:
    IntegratorContext createIntegratorContext(int recursionDepth);
    Scene &scene;
    std::shared_ptr<SceneIntersector> sceneIntersector;
};

} // crayg
