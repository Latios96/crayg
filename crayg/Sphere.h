//
// Created by jan on 19.08.18.
//

#ifndef CRAYG_SPHERE_H
#define CRAYG_SPHERE_H


#include "Intersectable.h"
#include "Transformable.h"

class Sphere : Intersectable, Transformable {
public:
    Vector3f intersect(Ray ray) override;
    bool intersects(Ray ray) override;

    Sphere(Vector3f position, float radius);

    float getRadius() const;

private:
    float radius;
};


#endif //CRAYG_SPHERE_H
