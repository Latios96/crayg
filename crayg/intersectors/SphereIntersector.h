//
// Created by Jan Honsbrok on 14.10.18.
//

#ifndef CRAYG_SPHEREINTERSECTOR_H
#define CRAYG_SPHEREINTERSECTOR_H

#include <schemas/SpherePrim.h>
#include "Intersector.h"

template <>
class Intersector<SpherePrim>{
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

    explicit Intersector(SpherePrim objectToIntersect) : sphereToIntersect(objectToIntersect) {}

private:
    SpherePrim sphereToIntersect;
};

Vector3f Intersector<SpherePrim>::intersect(Ray ray) {
    // todo implement
    return Vector3f();
}
// todo add tests
bool Intersector<SpherePrim>::isIntersecting(Ray ray) {
    ray.startPoint = ray.startPoint + sphereToIntersect.getPositionAttribute().getValue().invert();

    float b = 2.0f * (ray.startPoint.x * ray.direction.x +
                      ray.startPoint.y * ray.direction.y +
                      ray.startPoint.z * ray.direction.z);

    float radius = sphereToIntersect.getRadiusAttribute().getValue();
    float c = ray.startPoint.x * ray.startPoint.x +
              ray.startPoint.y * ray.startPoint.y +
              ray.startPoint.z * ray.startPoint.z - radius * radius;

    float d = b*b - (4.0f * c);

    return d >= 0.0f;
}

#endif //CRAYG_SPHEREINTERSECTOR_H
