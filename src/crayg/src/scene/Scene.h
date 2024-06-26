#pragma once

#include "RenderSettings.h"
#include "camera/Camera.h"
#include "lights/Light.h"
#include "scene/SceneObject.h"
#include "shadingnetworks/ShadingNode.h"
#include <memory>
#include <set>
#include <vector>

namespace crayg {

class Scene {
  public:
    Scene();
    explicit Scene(const RenderSettings &renderSettings);

    void addObject(const std::shared_ptr<SceneObject> &sceneObject);
    void addLight(const std::shared_ptr<Light> &sceneObject);

    std::vector<std::shared_ptr<SceneObject>> objects;
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Camera> camera = nullptr;
    RenderSettings renderSettings;

    std::size_t primitiveCount() const;

    virtual ~Scene() = default;
};

}
