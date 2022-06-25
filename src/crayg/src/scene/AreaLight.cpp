#include "AreaLight.h"

namespace crayg {

AreaLight::AreaLight() = default;

AreaLight::AreaLight(const Transform &transform, float intensity) : Light(transform, intensity) {}

float AreaLight::calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) {
    const Vector3f samplePosition = sampleLightShape();

    const Vector3f shadowVector = (samplePosition - point);
    const Vector3f normal = getNormal({0, 0, 0});
    if (normal.scalarProduct(shadowVector) > 0) {
        return Light::FULL_SHADOW;
    }
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
Light::Radiance AreaLight::radiance(const Vector3f &point, const Vector3f &normal) {
    const Vector3f shadowVector = sampleLightShape() - point;
    Ray shadowRay(point, shadowVector);// todo normalize this and pass length to ray

    if (getNormal({0, 0, 0}).scalarProduct(shadowVector) > 0) {
        return {0, shadowRay};
    }

    const float pdf = shadowVector.lengthSquared() / (normal.scalarProduct(shadowVector) * area());

    return {getIntensity() / pdf, shadowRay};
}

}


