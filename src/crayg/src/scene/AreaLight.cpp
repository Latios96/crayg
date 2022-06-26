#include "AreaLight.h"

namespace crayg {

AreaLight::AreaLight() = default;

AreaLight::AreaLight(const Transform &transform, float intensity) : Light(transform, intensity) {}

Light::Radiance AreaLight::radiance(const Vector3f &point, const Vector3f &normal) {
    const Vector3f shadowVector = sampleLightShape() - point;
    Ray shadowRay(point, shadowVector);// todo normalize this and pass length to ray

    if (getNormal({0, 0, 0}).scalarProduct(shadowVector) > 0) {
        return {Color::createBlack(), shadowRay};
    }

    const float pdf = shadowVector.lengthSquared() / (normal.scalarProduct(shadowVector) * area());

    return {getColor() * getIntensity() / pdf, shadowRay};
}

}


