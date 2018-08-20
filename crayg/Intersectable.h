//
// Created by jan on 19.08.18.
//

#ifndef CRAYG_INTERSECTABLE_H
#define CRAYG_INTERSECTABLE_H


#include "Vector3f.h"
#include "Ray.h"

class Intersectable {
public:
    /**
     * Intersects the given ray with the implementing object.
     * @param ray ray in world space to intersect with
     * @return the location of the object Surface
     */
    virtual Vector3f intersect(Ray ray)=0;
    /**
     * Returns if the ray intersects with the object, so implementation can optimize
     * @param ray ray in world space to intersect with
     * @return true if intersects else false
     */
    virtual bool intersects(Ray ray)=0;
};


#endif //CRAYG_INTERSECTABLE_H
