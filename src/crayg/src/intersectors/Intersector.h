//
// Created by Jan Honsbrok on 14.10.18.
//

#ifndef CRAYG_INTERSECTOR_H
#define CRAYG_INTERSECTOR_H

#include "basics/Vector3f.h"
#include "basics/Ray.h"

template<typename T>
class Intersector {
 public:
    /**
     * Intersects the given ray with the implementing object.
     * @param ray ray in world space to intersect with
     * @return the location of the object Surface
     */
    Vector3f intersect(Ray ray);
    /**
     * Returns if the ray intersects with the object, so implementation can optimize
     * @param ray ray in world space to intersect with
     * @return true if intersects else false
     */
    bool isIntersecting(Ray ray);

    explicit Intersector(T objectToIntersect) : sphereToIntersect(objectToIntersect) {}

 private:
    T sphereToIntersect;
};

#endif //CRAYG_INTERSECTOR_H
