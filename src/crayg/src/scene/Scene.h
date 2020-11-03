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
#include <memory>

// todo add Rendersettings
class Scene {
 public:
    Scene();
    Scene(const RenderSettings &renderSettings);

    void addObject(const std::shared_ptr<SceneObject> &sceneObject);
    void addLight(const std::shared_ptr<Light> &sceneObject);

    std::vector<std::shared_ptr<SceneObject>> objects;
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Camera> camera = nullptr;
    RenderSettings renderSettings;

    virtual ~Scene() = default;
};
#endif //CRAYG_SCENE_H
