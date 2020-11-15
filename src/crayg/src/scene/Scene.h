//
// Created by jan on 22.08.18.
//

#ifndef CRAYG_SCENE_H
#define CRAYG_SCENE_H

#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Camera.h"
#include "RenderSettings.h"
#include "ShadingNode.h"
#include <memory>


class Scene {
 public:
    Scene();
    explicit Scene(const RenderSettings &renderSettings);

    void addObject(const std::shared_ptr<SceneObject> &sceneObject);
    void addLight(const std::shared_ptr<Light> &sceneObject);
    void addMaterial(const std::shared_ptr<Material> &material);

    std::vector<std::shared_ptr<SceneObject>> objects;
    std::vector<std::shared_ptr<Light>> lights;
    std::vector<std::shared_ptr<Material>> materials;
    std::shared_ptr<Camera> camera = nullptr;
    RenderSettings renderSettings;
    bool materialWithNameExists(const std::shared_ptr<Material> &material);

    virtual ~Scene() = default;

};
#endif //CRAYG_SCENE_H
