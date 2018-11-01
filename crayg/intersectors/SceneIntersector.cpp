//
// Created by Jan Honsbrok on 01.11.18.
//

#include "SceneIntersector.h"
Vector3f SceneIntersector::intersect(Ray ray) {
    return {};
}

bool SceneIntersector::intersects(Ray ray) {
    for(const std::shared_ptr<Intersectable> &intersectable : scene.objects){
        if (intersectable->intersects(ray)) {
            return true;
        }
    }
    return false;
}

SceneIntersector::SceneIntersector(Scene &scene) : scene(scene) {}