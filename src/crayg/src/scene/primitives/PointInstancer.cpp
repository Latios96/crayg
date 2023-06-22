#include "PointInstancer.h"

namespace crayg {

std::string PointInstancer::getType() {
    return "PointInstancer";
}

Vector3f PointInstancer::getNormal(Vector3f point) {
    throw std::runtime_error("PointInstancer::getNormal is not supported.");
}

Imageable::Intersection PointInstancer::intersect(Ray ray) {
    throw std::runtime_error("PointInstancer::intersect is not supported.");
}

bool PointInstancer::isIntersecting(Ray ray) {
    throw std::runtime_error("PointInstancer::isIntersecting is not supported.");
}

BoundingBox PointInstancer::getBounds() const {
    throw std::runtime_error("PointInstancer::getBounds is not supported.");
}

} // crayg