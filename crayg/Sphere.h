//
// Created by jan on 19.08.18.
//

#ifndef CRAYG_SPHERE_H
#define CRAYG_SPHERE_H


#include "Intersectable.h"

class Sphere : Intersectable {
public:
    Vector3f intersect(Ray ray);
    bool intersects(Ray ray);

    Sphere(float radius);

    float getRadius() const;

private:
    float radius;
};


#endif //CRAYG_SPHERE_H
