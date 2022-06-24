#include <algorithm>
#include "SceneIntersector.h"

namespace crayg {

Imageable::Intersection SceneIntersector::intersect(const Ray &ray) const {
    Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

    for (const auto &intersectable : scene.objects) {
        Imageable::Intersection intersection = intersectable->intersect(ray);

        hitIntersection = Imageable::Intersection::nearest(intersection, hitIntersection);
    }
    return hitIntersection;
}

bool SceneIntersector::isIntersecting(const Ray &ray) const {
    return std::any_of(scene.objects.begin(),
                       scene.objects.end(),
                       [&ray](std::shared_ptr<Imageable> &intersectable) { return intersectable->isIntersecting(ray); });
}

SceneIntersector::SceneIntersector(Scene &scene) : scene(scene) {}

SceneIntersector::~SceneIntersector() = default;

bool Intersection::isValid() const {
    return object != nullptr;
}

}