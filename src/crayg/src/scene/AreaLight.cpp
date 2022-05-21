//
// Created by Jan on 21.05.2022.
//

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

}


