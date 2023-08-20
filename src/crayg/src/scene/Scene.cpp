#include "Scene.h"
#include <algorithm>
#include <fmt/format.h>

namespace crayg {

Scene::Scene(const RenderSettings &renderSettings) : renderSettings(renderSettings) {
}

void Scene::addLight(const std::shared_ptr<Light> &light) {
    lights.push_back(light);
}

void Scene::addObject(const std::shared_ptr<SceneObject> &sceneObject) {
    objects.push_back(sceneObject);
}

std::size_t Scene::primitiveCount() const {
    std::size_t primitiveCount = 0;
    for (auto &sceneObject : objects) {
        primitiveCount += sceneObject->primitiveCount();
    }
    return primitiveCount;
}

Scene::Scene() = default;

}