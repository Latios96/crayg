#include "AbstractIntegrator.h"

namespace crayg {
AbstractIntegrator::AbstractIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector)
    : scene(scene), sceneIntersector(sceneIntersector) {
}

AbstractIntegrator::~AbstractIntegrator() = default;
} // crayg