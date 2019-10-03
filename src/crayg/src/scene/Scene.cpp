//
// Created by jan on 22.08.18.
//

#include "Scene.h"

void Scene::addObject(SceneObject *intersectable) {
    objects.push_back(std::shared_ptr<SceneObject>(intersectable));
}

void Scene::addLight(Light *light) {
    lights.push_back(std::shared_ptr<Light>(light));
}

Scene::~Scene() {
    delete camera;
}

Scene::Scene() = default;
