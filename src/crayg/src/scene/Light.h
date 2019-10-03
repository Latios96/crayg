//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_LIGHT_H
#define CRAYG_LIGHT_H

#include "Sphere.h"

enum LightType {
    POINT_LIGHT
};

class Light : public Serializable, public Transformable {
 public:

    void serialize(Serializer &serializer) override;

    void deserialize(Deserializer &deserializer) override;
    float getIntensity() const;

    void setIntensity(float intensity);

    const LightType lightType = POINT_LIGHT;

 private:
    float intensity;
};

#endif //CRAYG_LIGHT_H