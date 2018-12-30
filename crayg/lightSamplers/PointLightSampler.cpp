//
// Created by jan on 30.12.18.
//

#include "PointLightSampler.h"

PointLightSampler::PointLightSampler(SceneIntersector &sceneIntersector, const Light &light) : LightSampler(
        sceneIntersector), light(light) {}

float PointLightSampler::calculateShadowFactor(const Vector3f &point) {
    // todo check if light has intensity of 0.0
    // todo quadratic falloff
    const Vector3f shadowVector = light.getPosition() - point;
    Ray shadowRay(point, shadowVector);
    const Imageable::Intersection intersection = sceneIntersector.intersect(shadowRay);
    
    const bool hasIntersection = intersection.imageable != nullptr;
    if (hasIntersection){
        const bool intersectionIsBehindLight = shadowVector.length() < intersection.rayParameter;
        if (intersectionIsBehindLight){
            return NO_SHADOW; 
        }
        else{
            return FULL_SHADOW;
        }
    }
    else{
        return NO_SHADOW;
    }
}
