//
// Created by jan on 22.08.18.
//

#ifndef CRAYG_SCENE_H
#define CRAYG_SCENE_H


#include <vector>
#include "Intersectable.h"

class Scene{
public:
    Scene();

    void addObject(Intersectable* intersectable);

    std::vector<std::shared_ptr<Intersectable>> objects;

};
class SceneIntersector : public Intersectable{
public:
    explicit SceneIntersector(Scene &scene);

    Vector3f intersect(Ray ray) override;
    bool intersects(Ray ray) override;

private:
    Scene &scene;
};

#endif //CRAYG_SCENE_H
