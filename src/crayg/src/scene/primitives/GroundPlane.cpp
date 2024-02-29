#include "GroundPlane.h"

namespace crayg {

bool GroundPlane::isIntersecting(Ray ray) {
    auto scalar = normal.dot(ray.direction);
    return scalar != 0;
}

Vector3f GroundPlane::getNormal(Vector3f point) {
    return normal;
}

Imageable::Intersection GroundPlane::intersect(Ray ray) {
    const float scalar = normal.dot(ray.direction);

    if (scalar == 0) {
        return Imageable::Intersection::createInvalid();
    } else {
        const float t = -(normal.dot(ray.startPoint) + getPosition().length()) / scalar;

        if (t > 0) {
            return {t, this, ImageableType::INVALID};
        }
        return Imageable::Intersection::createInvalid();
    }
}

BoundingBox GroundPlane::getBounds() const {
    return {{std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(),
             std::numeric_limits<float>::lowest()},
            {std::numeric_limits<float>::max(), 0, std::numeric_limits<float>::max()}};
}

std::string GroundPlane::getType() {
    return "GroundPlane";
}

}
