//
// Created by jan on 22.08.18.
//

#ifndef CRAYG_SCENE_H
#define CRAYG_SCENE_H


#include <vector>
#include "intersectors/Intersectable.h"
#include "Sphere.h"
#include "Light.h"

// todo add camera member and Rendersettings
class Scene{
public:
    Scene();

    void addObject(SceneObject* sceneObject);

    void addLight(Light* sceneObject);

    std::vector<std::shared_ptr<SceneObject>> objects;
    std::vector<std::shared_ptr<Light>> lights;

};
#endif //CRAYG_SCENE_H
