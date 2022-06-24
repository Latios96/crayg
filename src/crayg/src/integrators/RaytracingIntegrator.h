
#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_RAYTRACINGINTEGRATOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_RAYTRACINGINTEGRATOR_H_

#include "AbstractIntegrator.h"
#include "ShadingMethod.h"
namespace crayg {

class RaytracingIntegrator : public AbstractIntegrator {
 public:
    RaytracingIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector);
    Color integrate(const Ray &ray) override;
    Color integrate(const Ray &ray, int depth);
    static const int MAX_DEPTH = 2;
 private:
    ShadingMethod lambertMethod;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTEGRATORS_RAYTRACINGINTEGRATOR_H_
