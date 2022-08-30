
#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORFACTORY_H_

#include "IntegratorType.h"
#include "AbstractIntegrator.h"
#include "RaytracingIntegrator.h"
#include "DebugIntegrator.h"
#include "AmbientOcclusionIntegrator.h"
#include <magic_enum.hpp>

namespace crayg {

class IntegratorFactory {
 public:
    static AbstractIntegrator *createIntegrator(const IntegratorType &integratorType,
                                                Scene &scene,
                                                const std::shared_ptr<SceneIntersector> &sceneIntersector) {
        switch (integratorType) {
            case IntegratorType::RAYTRACING: return new RaytracingIntegrator(scene, sceneIntersector);
            case IntegratorType::DEBUG: return new DebugIntegrator(scene, sceneIntersector);
            case IntegratorType::AMBIENT_OCCLUSION: return new AmbientOcclusionIntegrator(scene, sceneIntersector);
            default:
                throw std::runtime_error(fmt::format(R"(Unsupported Integrator type: "{}")",
                                                     magic_enum::enum_name(integratorType)));
        }
    }
};

}

#endif //CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORFACTORY_H_
