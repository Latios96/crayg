//
// Created by jan on 19.08.18.
//

#ifndef CRAYG_INTERSECTABLE_H
#define CRAYG_INTERSECTABLE_H


#include "foundation/Vector3f.h"
#include "foundation/Ray.h"

class Intersectable{
public:
    /**
     * Returns if the ray intersects with the object, so implementation can optimize
     * @param ray ray in world space to intersect with
     * @return true if intersects else false
     */
    virtual bool isIntersecting(Ray ray)=0;

    virtual ~Intersectable() = default;
};


#endif //CRAYG_INTERSECTABLE_H
