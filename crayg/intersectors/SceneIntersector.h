//
// Created by Jan Honsbrok on 01.11.18.
//

#ifndef CRAYG_SCENEINTERSECTOR_H
#define CRAYG_SCENEINTERSECTOR_H


#include <scene/Scene.h>
#include "Intersectable.h"

struct Intersection{
public:
    Intersection(const Ray &ray, Vector3f location, SceneObject *object) : ray(ray), location(location), object(object) {}

    Ray ray;
    Vector3f location;
    SceneObject* object;

    bool isValid();
};

// todo add init method -> builds BVH Tree
class SceneIntersector{
public:
    explicit SceneIntersector(Scene &scene);

    Intersection intersect(Ray ray);
    bool intersects(Ray ray);

private:
    Scene &scene;
};


#endif //CRAYG_SCENEINTERSECTOR_H
