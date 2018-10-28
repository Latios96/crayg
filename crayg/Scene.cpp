//
// Created by jan on 22.08.18.
//

#include "Scene.h"


void Scene::addObject(Intersectable* intersectable) {
    objects.push_back(std::shared_ptr<Intersectable>(intersectable));
}

Scene::Scene() = default;

Vector3f Scene::intersect(Ray ray) {
    return Vector3f();
}

bool Scene::intersects(Ray ray) {
    for(const std::shared_ptr<Intersectable> &intersectable : objects){
        if (intersectable->intersects(ray)) {
            return true;
        }
    }
    return false;
}
