#include "IntegratorFactory.h"
#include "AmbientOcclusionIntegrator.h"
#include "DebugIntegrator.h"
#include "RaytracingIntegrator.h"
#include "utils/Exceptions.h"

namespace crayg {

AbstractIntegrator *IntegratorFactory::createIntegrator(const IntegratorType &integratorType, Scene &scene,
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
        CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format(R"(Unsupported Integrator type: "{}")", integratorType)));
    }
}
}