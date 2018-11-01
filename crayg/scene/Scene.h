//
// Created by jan on 22.08.18.
//

#ifndef CRAYG_SCENE_H
#define CRAYG_SCENE_H


#include <vector>
#include "Intersectable.h"
#include "Sphere.h"

class Scene{
public:
    Scene();

    void addObject(SceneObject* sceneObject);

    std::vector<std::shared_ptr<SceneObject>> objects;

};
// todo add tests
// todo move to own header/cpp file in intersectors
class SceneIntersector : public Intersectable{
public:
    explicit SceneIntersector(Scene &scene);

    Vector3f intersect(Ray ray) override;
    bool intersects(Ray ray) override;

private:
    Scene &scene;
};

#endif //CRAYG_SCENE_H
