#include "PointInstancer.h"

namespace crayg {

std::string PointInstancer::getType() {
    return "PointInstancer";
}

Vector3f PointInstancer::getNormal(Vector3f point) {
    CRAYG_LOG_AND_THROW(std::runtime_error("PointInstancer::getNormal is not supported."));
}

Imageable::Intersection PointInstancer::intersect(Ray ray) {
    CRAYG_LOG_AND_THROW(std::runtime_error("PointInstancer::intersect is not supported."));
}

bool PointInstancer::isIntersecting(Ray ray) {
    CRAYG_LOG_AND_THROW(std::runtime_error("PointInstancer::isIntersecting is not supported."));
}

BoundingBox PointInstancer::getBounds() const {
    CRAYG_LOG_AND_THROW(std::runtime_error("PointInstancer::getBounds is not supported."));
}

void PointInstancer::init() {
    auto &instancerTransform = getTransform();
    for (auto &transform : transforms) {
        transform = instancerTransform * transform;
    }
}

} // crayg