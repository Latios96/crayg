//
// Created by Jan Honsbrok on 01.11.18.
//

#ifndef CRAYG_SCENEINTERSECTOR_H
#define CRAYG_SCENEINTERSECTOR_H


#include <scene/Scene.h>
#include "Intersectable.h"

// todo add tests
class SceneIntersector : public Intersectable{
public:
    explicit SceneIntersector(Scene &scene);

    Vector3f intersect(Ray ray) override;
    bool intersects(Ray ray) override;

private:
    Scene &scene;
};


#endif //CRAYG_SCENEINTERSECTOR_H
