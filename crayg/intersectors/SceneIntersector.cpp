//
// Created by Jan Honsbrok on 01.11.18.
//

#include "SceneIntersector.h"
Imageable::Intersection SceneIntersector::intersect(Ray ray) {
    Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

    for(const auto &intersectable : scene.objects){
        Imageable::Intersection intersection = intersectable->intersect(ray);

        if(intersection.rayParameter< hitIntersection.rayParameter ){
            hitIntersection = intersection;
        }
    }
    return hitIntersection;
}

bool SceneIntersector::isIntersecting(Ray ray){
    for(const auto &intersectable : scene.objects){
        if (intersectable->isIntersecting(ray)) {
            return true;
        }
    }
    return false;
}

SceneIntersector::SceneIntersector(Scene &scene) : scene(scene) {}

bool Intersection::isValid() {
    return object != nullptr;
}
