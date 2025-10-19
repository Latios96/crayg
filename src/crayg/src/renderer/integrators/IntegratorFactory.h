
#pragma once

#include "AbstractIntegrator.h"
#include "IntegratorType.h"

namespace crayg {

class IntegratorFactory {
  public:
    static AbstractIntegrator *createIntegrator(const IntegratorType &integratorType, Scene &scene,
                                                const std::shared_ptr<SceneIntersector> &sceneIntersector,
                                                const IntegratorSettings &integratorSettings);
};

}
