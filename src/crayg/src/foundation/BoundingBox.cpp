//
// Created by jan on 02.12.18.
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(const Vector3f &min, const Vector3f &max) : min(min), max(max) {}

bool BoundingBox::operator==(const BoundingBox &rhs) const {
    return min == rhs.min &&
           max == rhs.max;
}

bool BoundingBox::operator!=(const BoundingBox &rhs) const {
    return !(rhs == *this);
}

BoundingBox::BoundingBox() {
    min = Vector3f();
    max = Vector3f();
}

bool BoundingBox::isIntersecting(const Ray &ray) {
    float tmin = (min.x - ray.startPoint.x) / ray.direction.x;
    float tmax = (max.x - ray.startPoint.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (min.y - ray.startPoint.y) / ray.direction.y;
    float tymax = (max.y - ray.startPoint.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min.z - ray.startPoint.z) / ray.direction.z;
    float tzmax = (max.z - ray.startPoint.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;

}


