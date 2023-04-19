#include "Ray.h"
#include <limits>
#include <utils/Preconditions.h>

namespace crayg {

Ray::Ray(Vector3f startPoint, Vector3f direction) {
    CRAYG_CHECKD_IS_NORMALIZED_VECTOR(direction);
    this->startPoint = startPoint;
    this->direction = direction;
    this->length = std::numeric_limits<float>::min();
}

Ray::Ray(Vector3f startPoint, Vector3f direction, float length) {
    CRAYG_CHECKD_IS_NORMALIZED_VECTOR(direction);
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
    return startPoint == rhs.startPoint && direction == rhs.direction && length == rhs.length;
}

bool Ray::operator!=(const Ray &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "startPoint: " << ray.startPoint << " direction: " << ray.direction << " length: " << ray.length;
    return os;
}

Ray Ray::offsetStartPointBy(float offset) const {
    return Ray(startPoint + direction * offset, direction, length);
}

}
