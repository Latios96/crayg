//
// Created by jan on 22.08.18.
//

#include "Scene.h"


void Scene::addObject(SceneObject* intersectable) {
    objects.push_back(std::shared_ptr<SceneObject>(intersectable));
}

Scene::Scene() = default;

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
