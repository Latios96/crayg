#include <algorithm>
#include <fmt/format.h>
#include "Scene.h"

namespace crayg {

Scene::Scene(const RenderSettings &renderSettings) : renderSettings(renderSettings) {}

void Scene::addLight(const std::shared_ptr<Light> &light) {
    lights.push_back(light);
}
void Scene::addObject(const std::shared_ptr<SceneObject> &sceneObject) {
    objects.push_back(sceneObject);
    owningObjects.push_back(sceneObject);
    addMaterialIfObjectHasMaterial(sceneObject);

}
void Scene::addObject(const std::shared_ptr<TriangleMesh> &triangleMesh) {
    triangleMesh->getTriangles(objects);
    owningObjects.push_back(triangleMesh);
    if (triangleMesh->getMaterial()) {
        if (std::find(materials.begin(), materials.end(), triangleMesh->getMaterial()) == materials.end()) {
            addMaterial(triangleMesh->getMaterial());
        }
    }
}
void Scene::addMaterialIfObjectHasMaterial(const std::shared_ptr<SceneObject> &sceneObject) {
    if (sceneObject->getMaterial()) {
        if (std::find(materials.begin(), materials.end(), sceneObject->getMaterial()) == materials.end()) {
            addMaterial(sceneObject->getMaterial());
        }
    }
}

void Scene::addMaterial(const std::shared_ptr<Material> &material) {
    if (material->getName().empty()) {
        throw std::runtime_error("Material has no name!");
    }
    if (!materialWithNameExists(material)) {
        materials.insert(material);
    }
}
bool Scene::materialWithNameExists(const std::shared_ptr<Material> &material) {
    return std::any_of(materials.begin(),
                       materials.end(),
                       [&material](const std::shared_ptr<Material> &mat) {
                           return mat->getName() == material->getName();
                       });
}
std::shared_ptr<Material> Scene::materialByName(const std::string &name) {
    const auto iterator = std::find_if(materials.begin(),
                                       materials.end(),
                                       [&name](std::shared_ptr<Material> material) {
                                           return name == material->getName();
                                       });
    if (iterator == materials.end()) {
        return nullptr;
    }
    return *iterator;
}

Scene::Scene() = default;

}