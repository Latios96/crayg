//
// Created by Jan Honsbrok on 01.11.18.
//

#include <algorithm>
#include "SceneIntersector.h"

namespace crayg {

Imageable::Intersection SceneIntersector::intersect(const Ray &ray) const {
    Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

    for (const auto &intersectable : scene.objects) {
        Imageable::Intersection intersection = intersectable->intersect(ray);

        if (intersection.rayParameter < hitIntersection.rayParameter && intersection.imageable) {
            hitIntersection.rayParameter = intersection.rayParameter;
            hitIntersection.imageable = intersection.imageable;
        }
    }
    return hitIntersection;
}

bool SceneIntersector::isIntersecting(const Ray &ray) const {
    return std::any_of(scene.objects.begin(),
                       scene.objects.end(),
                       [&ray](std::shared_ptr<SceneObject> &intersectable) { return intersectable->isIntersecting(ray); });
}

SceneIntersector::SceneIntersector(Scene &scene) : scene(scene) {}

SceneIntersector::~SceneIntersector() {

}

bool Intersection::isValid() {
    return object != nullptr;
}

}