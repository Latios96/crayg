//
// Created by jan on 22.08.18.
//

#include "Scene.h"

void Scene::addLight(const std::shared_ptr<Light> &light) {
    lights.push_back(light);
}
void Scene::addObject(const std::shared_ptr<SceneObject> &sceneObject) {
    objects.push_back(sceneObject);
    if (sceneObject->getMaterial()) {
        if (std::find(materials.begin(), materials.end(), sceneObject->getMaterial()) == materials.end()) {
            materials.push_back(sceneObject->getMaterial());
        }
    }
}
Scene::Scene(const RenderSettings &renderSettings) : renderSettings(renderSettings) {}

Scene::Scene() = default;
