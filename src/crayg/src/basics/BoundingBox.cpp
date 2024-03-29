#include "BoundingBox.h"
#include <utils/ToStringHelper.h>

namespace crayg {

BoundingBox::BoundingBox(const Vector3f &min, const Vector3f &max) : min(min), max(max) {
}

bool BoundingBox::operator==(const BoundingBox &rhs) const {
    return min == rhs.min && max == rhs.max;
}

bool BoundingBox::operator!=(const BoundingBox &rhs) const {
    return !(rhs == *this);
}

BoundingBox::BoundingBox() {
    min = Vector3f();
    max = Vector3f();
}

bool BoundingBox::isIntersecting(const Ray &ray) const {
    float txmin = (min.x - ray.startPoint.x) / ray.direction.x;
    float txmax = (max.x - ray.startPoint.x) / ray.direction.x;

    if (txmin > txmax) {
        std::swap(txmin, txmax);
    }

    float tymin = (min.y - ray.startPoint.y) / ray.direction.y;
    float tymax = (max.y - ray.startPoint.y) / ray.direction.y;

    if (tymin > tymax) {
        std::swap(tymin, tymax);
    }

    if ((txmin > tymax) || (tymin > txmax)) {
        return false;
    }

    if (tymin > txmin) {
        txmin = tymin;
    }

    if (tymax < txmax) {
        txmax = tymax;
    }

    float tzmin = (min.z - ray.startPoint.z) / ray.direction.z;
    float tzmax = (max.z - ray.startPoint.z) / ray.direction.z;

    if (tzmin > tzmax) {
        std::swap(tzmin, tzmax);
    }

    if ((txmin > tzmax) || (tzmin > txmax)) {
        return false;
    }

    if (tzmin > txmin) {
        txmin = tzmin;
    }

    if (tzmax < txmax) {
        txmax = tzmax;
    }

    return true;
}

std::ostream &operator<<(std::ostream &os, const BoundingBox &box) {
    os << "BoundingBox{min: " << box.min << " max: " << box.max << '}';
    return os;
}

BoundingBox BoundingBox::unionWith(const Vector3f &point) const {
    BoundingBox boundingBox(min, max);
    if (point.x < min.x) {
        boundingBox.min.x = point.x;
    }
    if (point.y < min.y) {
        boundingBox.min.y = point.y;
    }
    if (point.z < min.z) {
        boundingBox.min.z = point.z;
    }

    if (point.x > max.x) {
        boundingBox.max.x = point.x;
    }
    if (point.y > max.y) {
        boundingBox.max.y = point.y;
    }
    if (point.z > max.z) {
        boundingBox.max.z = point.z;
    }
    return boundingBox;
}

BoundingBox BoundingBox::unionWith(const BoundingBox &boundingBox) const {
    BoundingBox resultBoundingBox(min, max);
    if (boundingBox.min.x < min.x) {
        resultBoundingBox.min.x = boundingBox.min.x;
    }
    if (boundingBox.min.y < min.y) {
        resultBoundingBox.min.y = boundingBox.min.y;
    }
    if (boundingBox.min.z < min.z) {
        resultBoundingBox.min.z = boundingBox.min.z;
    }

    if (boundingBox.max.x > max.x) {
        resultBoundingBox.max.x = boundingBox.max.x;
    }
    if (boundingBox.max.y > max.y) {
        resultBoundingBox.max.y = boundingBox.max.y;
    }
    if (boundingBox.max.z > max.z) {
        resultBoundingBox.max.z = boundingBox.max.z;
    }
    return resultBoundingBox;
}

BoundingBox BoundingBox::fromCenterAndRadius(const Vector3f &center, const float radius) {
    return {{center.x - radius, center.y - radius, center.z - radius},
            {center.x + radius, center.y + radius, center.z + radius}};
}

Vector3f BoundingBox::getCentroid() const {
    const Vector3f middle = max - min;
    return min + (middle * 0.5f);
}

}
