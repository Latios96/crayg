#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_DEBUGINTEGRATOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_DEBUGINTEGRATOR_H_

#include "AbstractIntegrator.h"

namespace crayg {

class DebugIntegrator : public AbstractIntegrator {
 public:
    DebugIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector);
    Color integrate(const Ray &ray, int recursionDepth) override;
    ~DebugIntegrator() override;
};
}

#endif //CRAYG_SRC_CRAYG_SRC_INTEGRATORS_DEBUGINTEGRATOR_H_
