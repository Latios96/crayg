//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_LIGHT_H
#define CRAYG_LIGHT_H

#include "Sphere.h"

enum LightType {
    POINT_LIGHT
};

class SceneIntersector;

class Light : public Serializable, public Transformable {
 public:

    void serialize(Serializer &serializer) override;

    void deserialize(Deserializer &deserializer) override;
    float getIntensity() const;

    void setIntensity(float intensity);

    const LightType lightType = POINT_LIGHT;

    float calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point);

 private:
    float intensity;
    constexpr static const float NO_SHADOW = 1.0f;
    constexpr static const float FULL_SHADOW = 0.0f;
};

#endif //CRAYG_LIGHT_H