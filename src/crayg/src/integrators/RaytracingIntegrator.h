
#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_RAYTRACINGINTEGRATOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_RAYTRACINGINTEGRATOR_H_

#include "AbstractIntegrator.h"

namespace crayg {

class RaytracingIntegrator : public AbstractIntegrator {
 public:
    RaytracingIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector);
    Color integrate(const Ray &ray, int recursionDepth) override;
    Color calculateDirectLight(std::shared_ptr<Light> &sharedPtr, const Vector3f &location, const Vector3f &normal);
    Color calculateIndirectLight(const SurfaceInteraction &surfaceInteraction,
                                 const OrthonormalBasis &orthonormalBasis,
                                 IntegratorContext &integratorContext);
 private:
    static const int MAX_RECURSION_DEPTH = 6;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTEGRATORS_RAYTRACINGINTEGRATOR_H_
