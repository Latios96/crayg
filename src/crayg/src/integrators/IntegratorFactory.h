
#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORFACTORY_H_

#include "AbstractIntegrator.h"
#include "AmbientOcclusionIntegrator.h"
#include "DebugIntegrator.h"
#include "IntegratorType.h"
#include "RaytracingIntegrator.h"
#include "utils/Exceptions.h"
#include <magic_enum.hpp>

namespace crayg {

class IntegratorFactory {
  public:
    static AbstractIntegrator *createIntegrator(const IntegratorType &integratorType, Scene &scene,
                                                const std::shared_ptr<SceneIntersector> &sceneIntersector,
                                                const IntegratorSettings &integratorSettings) {
        switch (integratorType) {
        case IntegratorType::RAYTRACING:
            return new RaytracingIntegrator(scene, sceneIntersector, integratorSettings);
        case IntegratorType::DEBUG:
            return new DebugIntegrator(scene, sceneIntersector);
        case IntegratorType::AMBIENT_OCCLUSION:
            return new AmbientOcclusionIntegrator(scene, sceneIntersector, integratorSettings);
        default:
            CRAYG_LOG_AND_THROW(
                std::runtime_error(fmt::format(R"(Unsupported Integrator type: "{}")", integratorType)));
        }
    }
};

}

#endif // CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORFACTORY_H_
