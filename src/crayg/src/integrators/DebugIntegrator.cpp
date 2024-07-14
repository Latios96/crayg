#include "DebugIntegrator.h"

namespace crayg {

DebugIntegrator::DebugIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector)
    : AbstractIntegrator(scene, sceneIntersector) {
}

Color DebugIntegrator::integrate(const Ray &ray, int recursionDepth) {
    thread_local HitStorage hitStorage;
    auto intersection = sceneIntersector->intersect(ray, hitStorage);

    const bool hasHit = intersection.imageable != nullptr;
    if (!hasHit) {
        return Color::createBlack();
    }

    const Vector3f location = ray.constructIntersectionPoint(intersection.rayParameter);
    const Vector3f normal = intersection.imageable->getNormal(location);
    const float scalar = normal.dot(ray.direction.invert());
    return Color::createGrey(std::max(scalar, 0.0f));
}

DebugIntegrator::~DebugIntegrator() = default;

}
