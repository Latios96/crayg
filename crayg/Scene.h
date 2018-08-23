//
// Created by jan on 22.08.18.
//

#ifndef CRAYG_SCENE_H
#define CRAYG_SCENE_H


#include "Intersectable.h"
#include <vector>

class Scene : Intersectable{
public:
    Scene();

    void addObject(Intersectable* intersectable);

    Vector3f intersect(Ray ray) override;
    bool intersects(Ray ray) override;

    ~Scene();

private:
    std::vector<Intersectable*> objects;

};


#endif //CRAYG_SCENE_H
