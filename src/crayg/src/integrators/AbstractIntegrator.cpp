#include "AbstractIntegrator.h"

namespace crayg {
AbstractIntegrator::AbstractIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector)
    : scene(scene), sceneIntersector(sceneIntersector) {
}

IntegratorContext AbstractIntegrator::createIntegratorContext(int recursionDepth) {
    return IntegratorContext(*this, recursionDepth);
}

AbstractIntegrator::~AbstractIntegrator() = default;
} // crayg