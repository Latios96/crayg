//
// Created by jan on 02.12.18.
//

#include "BoundingBox.h"

namespace crayg {

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
    float txmin = (min.x - ray.startPoint.x) / ray.direction.x;
    float txmax = (max.x - ray.startPoint.x) / ray.direction.x;

    if (txmin > txmax) std::swap(txmin, txmax);

    float tymin = (min.y - ray.startPoint.y) / ray.direction.y;
    float tymax = (max.y - ray.startPoint.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((txmin > tymax) || (tymin > txmax))
        return false;

    if (tymin > txmin)
        txmin = tymin;

    if (tymax < txmax)
        txmax = tymax;

    float tzmin = (min.z - ray.startPoint.z) / ray.direction.z;
    float tzmax = (max.z - ray.startPoint.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((txmin > tzmax) || (tzmin > txmax))
        return false;

    if (tzmin > txmin)
        txmin = tzmin;

    if (tzmax < txmax)
        txmax = tzmax;

    return true;

}

}

