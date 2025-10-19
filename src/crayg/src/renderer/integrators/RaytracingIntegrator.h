
#pragma once

#include "AbstractIntegrator.h"

namespace crayg {

class RaytracingIntegrator : public AbstractIntegrator {
  public:
    RaytracingIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector,
                         const IntegratorSettings &integratorSettings);
    Color integrate(const Ray &ray, int recursionDepth, RayType rayType) override;
    Color calculateDirectLight(std::shared_ptr<Light> &sharedPtr, const Vector3f &location, const Vector3f &normal);

  private:
    static const int MAX_RECURSION_DEPTH = 6;
    bool useGi = false;
};

}
