//
// Created by jan on 22.08.18.
//

#include "Scene.h"


void Scene::addObject(SceneObject* intersectable) {
    objects.push_back(std::shared_ptr<SceneObject>(intersectable));
}

Scene::Scene() = default;
