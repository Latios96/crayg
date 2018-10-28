//
// Created by jan on 22.08.18.
//

#ifndef CRAYG_SCENE_H
#define CRAYG_SCENE_H


#include <vector>
#include "Intersectable.h"

class Scene/* : public Intersectable*/{
public:
    Scene();

    void addObject(Intersectable* intersectable);

    Vector3f intersect(Ray ray);
    bool intersects(Ray ray);

private:
    std::vector<std::shared_ptr<Intersectable>> objects;

};


#endif //CRAYG_SCENE_H
