//
// Created by Jan on 20.11.2020.
//

#include "PointLight.h"
#include "intersectors/SceneIntersector.h"

float PointLight::calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) {
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
