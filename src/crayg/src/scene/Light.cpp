//
// Created by Jan Honsbrok on 04.11.18.
//

#include "Light.h"
#include "intersectors/SceneIntersector.h"

float Light::getIntensity() const {
    return intensity;
}

void Light::setIntensity(float intensity) {
    Light::intensity = intensity;
}

void Light::serialize(Serializer &serializer) {
    serializer.writeVector3f("position", this->getPosition());
    serializer.writeFloat("intensity", intensity);
}

void Light::deserialize(Deserializer &deserializer) {
    if (deserializer.hasProperty("position")) {
        setPosition(deserializer.readVector3f("position"));
        return;
    }
    transform = Transform(deserializer.readMatrix4x4f("transform"));
    setIntensity(deserializer.readFloat("intensity"));
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




