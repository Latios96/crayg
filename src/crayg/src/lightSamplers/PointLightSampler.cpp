//
// Created by jan on 30.12.18.
//

#include "PointLightSampler.h"

PointLightSampler::PointLightSampler(SceneIntersector &sceneIntersector, const Light &light) : LightSampler(
    sceneIntersector), light(light) {}

float PointLightSampler::calculateShadowFactor(const Vector3f &point) {
    const Vector3f shadowVector = light.getPosition() - point;
    Ray shadowRay(point, shadowVector.normalize());
    const Imageable::Intersection intersection = sceneIntersector.intersect(shadowRay);

    const bool hasIntersection = intersection.imageable != nullptr;
    if (hasIntersection) {
        const bool intersectionIsBehindLight = shadowVector.length() <= intersection.rayParameter;
        if (intersectionIsBehindLight) {
            return NO_SHADOW;
        } else {
            return FULL_SHADOW;
        }
    } else {
        return NO_SHADOW;
    }
}
