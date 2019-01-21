//
// Created by Jan Honsbrok on 04.11.18.
//

#include <lightSamplers/PointLightSampler.h>
#include "Light.h"

float Light::getIntensity() const {
    return intensity;
}

void Light::setIntensity(float intensity) {
    Light::intensity = intensity;
}

void Light::serialize(Serializer &serializer) {
    serializer.writeVector3f("position", this->getPosition());
    serializer.writeFloat("intensity", intensity);
    serializer.writeType("Light");
}

void Light::deserialize(Deserializer &deserializer) {
    setPosition(deserializer.readVector3f("position"));
    setIntensity(deserializer.readFloat("intensity"));
}




