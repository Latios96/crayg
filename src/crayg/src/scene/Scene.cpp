//
// Created by jan on 22.08.18.
//

#include <algorithm>
#include <fmt/format.h>
#include "Scene.h"

void Scene::addLight(const std::shared_ptr<Light> &light) {
    lights.push_back(light);
}
void Scene::addObject(const std::shared_ptr<SceneObject> &sceneObject) {
    objects.push_back(sceneObject);
    if (sceneObject->getMaterial()) {
        if (std::find(materials.begin(), materials.end(), sceneObject->getMaterial()) == materials.end()) {
            addMaterial(sceneObject->getMaterial());
        }
    }
}
Scene::Scene(const RenderSettings &renderSettings) : renderSettings(renderSettings) {}

void Scene::addMaterial(const std::shared_ptr<Material> &material) {
    if (material->getName().empty()) {
        throw std::runtime_error("Material has no name!");
    }
    if (materialWithNameExists(material)) {
        throw std::runtime_error(fmt::format("Material with name {}already exists!", material->getName()));
    }
    materials.push_back(material);
}
bool Scene::materialWithNameExists(const std::shared_ptr<Material> &material) {
    return std::any_of(materials.begin(),
                       materials.end(),
                       [&material](const std::shared_ptr<Material> &mat) {
                           return mat->getName() == material->getName();
                       });
}

Scene::Scene() = default;
