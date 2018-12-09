//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_LIGHT_H
#define CRAYG_LIGHT_H


#include "Sphere.h"

class Light : public Serializable, public Transformable{
public:

    void serialize(Serializer& serializer) override;

    void deserialize(Deserializer& deserializer) override;
    float getIntensity() const;

    void setIntensity(float intensity);

private:
    float intensity;
};


#endif //CRAYG_LIGHT_H