#include "AreaLight.h"
#include <boost/math/constants/constants.hpp>

namespace crayg {

AreaLight::AreaLight() = default;

AreaLight::AreaLight(const Transform &transform, float intensity) : Light(transform, intensity) {
}

Vector3f AreaLight::getNormal(Vector3f point) {
    return transform.applyForNormal({0, 0, 1}).normalize();
}

Light::Radiance AreaLight::radiance(const Vector3f &point, const Vector3f &normal) {
    const Vector3f &pointOnLight = sampleLightShape();
    const Ray shadowRay(point, pointOnLight - point);
    const Vector3f L = shadowRay.direction.normalize();
    const float angleBetweenSurfaceNormalAndLight = normal.dot(L);
    const float angleBetweenLightAndLightVector = -getNormal(pointOnLight).dot(L);

    if (angleBetweenSurfaceNormalAndLight <= 0.0f && angleBetweenLightAndLightVector <= 0.0f) {
        return {Color::createBlack(), shadowRay};
    }

    float weight = angleBetweenSurfaceNormalAndLight * angleBetweenLightAndLightVector * area() /
                   (boost::math::constants::pi<float>() * shadowRay.direction.lengthSquared());
    return {getColor() * getIntensity() * std::max(weight, 0.f), shadowRay};
}

}
