#include "SceneIntersector.h"
#include <algorithm>

namespace crayg {

Imageable::Intersection SceneIntersector::intersect(const Ray &ray) const {
    Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

    for (const auto &intersectable : scene.objects) {
        Imageable::Intersection intersection = intersectable->intersect(ray);

        hitIntersection = Imageable::Intersection::nearest(intersection, hitIntersection);
    }
    return hitIntersection;
}

bool SceneIntersector::isIntersecting(const Ray &ray, float maxDistance) const {
    return std::any_of(scene.objects.begin(), scene.objects.end(), [&ray](std::shared_ptr<SceneObject> &intersectable) {
        return intersectable->isIntersecting(ray);
    });
}

SceneIntersector::SceneIntersector(Scene &scene) : scene(scene) {
}

SceneIntersector::~SceneIntersector() = default;

}