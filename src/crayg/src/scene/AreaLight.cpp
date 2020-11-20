//
// Created by Jan on 20.11.2020.
//

#include "AreaLight.h"
#include "intersectors/SceneIntersector.h"

float AreaLight::calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) {
    float randomForWidth = (double(rand()) / RAND_MAX) * 2 - 1;
    float randomForHeight = (double(rand()) / RAND_MAX) * 2 - 1;
    Vector3f positionOnPlane = {randomForWidth, randomForHeight, 0};
    const Vector3f transformedPosition = getTransform().apply(positionOnPlane);

    const Vector3f shadowVector = transformedPosition - point;
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
void AreaLight::serialize(Serializer &serializer) {
    Light::serialize(serializer);
    serializer.writeType("AreaLight");
    serializer.writeFloat("width", width);
    serializer.writeFloat("height", height);
}
void AreaLight::deserialize(Deserializer &deserializer) {
    Light::deserialize(deserializer);
    width = deserializer.readFloat("width");
    height = deserializer.readFloat("height");
}
std::string AreaLight::getType() {
    return "AreaLight";
}
