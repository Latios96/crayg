#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_AMBIENTOCCLUSIONINTEGRATOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_AMBIENTOCCLUSIONINTEGRATOR_H_

#include "AbstractIntegrator.h"
#include "IntegratorSettings.h"

namespace crayg {

class AmbientOcclusionIntegrator : public AbstractIntegrator {
  public:
    AmbientOcclusionIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector,
                               const IntegratorSettings &integratorSettings);
    Color integrate(const Ray &ray, int recursionDepth) override;
    Color calculateAmbientOcclusionAtPoint(Imageable::Intersection &intersection, const Vector3f &location) const;

  private:
    int sampleCount;
    float radius;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_INTEGRATORS_AMBIENTOCCLUSIONINTEGRATOR_H_
