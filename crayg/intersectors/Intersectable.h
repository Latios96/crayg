//
// Created by jan on 19.08.18.
//

#ifndef CRAYG_INTERSECTABLE_H
#define CRAYG_INTERSECTABLE_H


#include "foundation/Vector3f.h"
#include "foundation/Ray.h"

class Intersectable {
public:
    /**
     * Intersects the given ray with the implementing object.
     * @param ray ray in world space to intersect with
     * @return the location of the object Surface
     */
    virtual Ray intersect(Ray ray)=0;
    /**
     * Returns if the ray intersects with the object, so implementation can optimize
     * @param ray ray in world space to intersect with
     * @return true if intersects else false
     */
    virtual bool intersects(Ray ray)=0;

    virtual ~Intersectable() = default;

    // todo intersectable should contain a factory method for an Intersector?

};



#endif //CRAYG_INTERSECTABLE_H
