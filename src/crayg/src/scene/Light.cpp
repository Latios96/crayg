//
// Created by Jan Honsbrok on 04.11.18.
//

#include "Light.h"
#include "intersectors/SceneIntersector.h"
#include "EmissiveMaterial.h"

namespace crayg {

float Light::getIntensity() const {
    return intensity;
}

void Light::setIntensity(float intensity) {
    Light::intensity = intensity;
}

float Light::calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) {
    const Vector3f shadowVector = getPosition() - point;
    Ray shadowRay(point, shadowVector.normalize());
    const Imageable::Intersection intersection = sceneIntersector.intersect(shadowRay);

    const bool hasIntersection = intersection.imageable != nullptr;
    if (hasIntersection) {
        const bool intersectionIsBehindLight = shadowVector.length() <= intersection.rayParameter;
        if (intersectionIsBehindLight) {
            return Light::NO_SHADOW;
        } else {
            return Light::FULL_SHADOW;
        }
    } else {
        return Light::NO_SHADOW;
    }
}
std::string Light::getType() {
    return "Light";
}
Vector3f Light::getNormal(Vector3f point) {
    return Vector3f();
}
Imageable::Intersection Light::intersect(Ray ray) {
    return Imageable::Intersection::createInvalid();
}
bool Light::isIntersecting(Ray ray) {
    return false;
}

Light::Light(const Transform &transform, float intensity) : Transformable(transform), intensity(intensity) {

}
BoundingBox Light::getBounds() const {
    return BoundingBox();
}
const std::string &Light::getName() const {
    return name;
}
void Light::setName(const std::string &name) {
    Light::name = name;
}
Light::Light() = default;

}



