#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_ABSTRACTINTEGRATOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_ABSTRACTINTEGRATOR_H_

#include "basics/Color.h"
#include "basics/Ray.h"
#include "intersectors/SceneIntersector.h"
#include "IntegratorContext.h"

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

#endif //CRAYG_SRC_CRAYG_SRC_INTEGRATORS_ABSTRACTINTEGRATOR_H_
