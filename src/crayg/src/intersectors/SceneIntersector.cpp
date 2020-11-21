//
// Created by Jan Honsbrok on 01.11.18.
//

#include "SceneIntersector.h"
Imageable::Intersection SceneIntersector::intersect(const Ray &ray) const {
    Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

    for (const auto &intersectable : scene.objects) {
        Imageable::Intersection intersection = intersectable->intersect(ray);

        if (intersection.rayParameter < hitIntersection.rayParameter && intersection.imageable) {
            hitIntersection.rayParameter = intersection.rayParameter;
            hitIntersection.imageable = intersection.imageable;
        }
    }
    for (const auto &intersectable : scene.lights) {
        Imageable::Intersection intersection = intersectable->intersect(ray);

        if (intersection.rayParameter < hitIntersection.rayParameter && intersection.imageable) {
            hitIntersection.rayParameter = intersection.rayParameter;
            hitIntersection.imageable = intersection.imageable;
        }
    }
    return hitIntersection;
}

bool SceneIntersector::isIntersecting(const Ray &ray) const {
    for (const auto &intersectable : scene.objects) {
        if (intersectable->isIntersecting(ray)) {
            return true;
        }
    }
    for (const auto &intersectable : scene.lights) {
        if (intersectable->isIntersecting(ray)) {
            return true;
        }
    }
    return false;
}

SceneIntersector::SceneIntersector(Scene &scene) : scene(scene) {}

SceneIntersector::~SceneIntersector() {

}

bool Intersection::isValid() {
    return object != nullptr;
}
