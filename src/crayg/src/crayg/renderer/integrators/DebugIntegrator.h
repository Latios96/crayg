#pragma once

#include "AbstractIntegrator.h"

namespace crayg {

class DebugIntegrator : public AbstractIntegrator {
  public:
    DebugIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector);
    Color integrate(const Ray &ray, int recursionDepth, RayType rayType) override;
    ~DebugIntegrator() override;
};
}
