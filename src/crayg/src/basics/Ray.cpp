//
// Created by jan on 16.08.18.
//

#include <limits>
#include <utils/ToStringHelper.h>
#include <Preconditions.h>
#include "Ray.h"

namespace crayg {

Ray::Ray(Vector3f startPoint, Vector3f direction) {
    Preconditions::checkIsUnitVector(direction, FAILURE_INFORMATION);
    this->startPoint = startPoint;
    this->direction = direction;
    this->length = std::numeric_limits<float>::min();
}

Ray::Ray(Vector3f startPoint, Vector3f direction, float length) {
    Preconditions::checkIsUnitVector(direction, FAILURE_INFORMATION);
    this->startPoint = startPoint;
    this->direction = direction;
    this->length = length;
}

Ray Ray::createInvalid() {
    return {Vector3f::createInvalid(), Vector3f::createInvalid(), std::numeric_limits<float>::max()};
}

bool Ray::isValid() {
    return startPoint.isValid() && direction.isValid() && length != std::numeric_limits<float>::max();
}

Vector3f Ray::constructIntersectionPoint() const {
    return startPoint + (direction * length);
}

Vector3f Ray::constructIntersectionPoint(float t) const {
    return startPoint + (direction * t);
}

bool Ray::operator==(const Ray &rhs) const {
    return startPoint == rhs.startPoint &&
        direction == rhs.direction &&
        length == rhs.length;
}

bool Ray::operator!=(const Ray &rhs) const {
    return !(rhs == *this);
}
std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "startPoint: " << ray.startPoint << " direction: " << ray.direction << " length: " << ray.length;
    return os;
}

}


