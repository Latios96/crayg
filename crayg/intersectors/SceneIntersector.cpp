//
// Created by Jan Honsbrok on 01.11.18.
//

#include "SceneIntersector.h"
Intersection SceneIntersector::intersect(Ray ray) {
    Ray hitRay(Vector3f(), Vector3f(), std::numeric_limits<float>::max());
    SceneObject* hitObject = nullptr;

    for(const auto &intersectable : scene.objects){
        Ray intersectionRay = intersectable->intersect(ray);

        if(intersectionRay.length < hitRay.length )
            hitRay = intersectionRay;
        hitObject = intersectable.get();
    }
    return {hitRay, hitRay.startPoint + (hitRay.direction * hitRay.length), hitObject};
}

bool SceneIntersector::intersects(Ray ray) {
    for(const auto &intersectable : scene.objects){
        if (intersectable->intersects(ray)) {
            return true;
        }
    }
    return false;
}

SceneIntersector::SceneIntersector(Scene &scene) : scene(scene) {}