//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_LIGHT_H
#define CRAYG_LIGHT_H

#include "sceneIO/Serializable.h"
#include "scene/Transformable.h"
#include "scene/Imageable.h"

class SceneIntersector;

class Light : public Serializable, public Transformable, public Imageable {
 public:

    void serialize(Serializer &serializer) override;

    void deserialize(Deserializer &deserializer) override;
    float getIntensity() const;

    void setIntensity(float intensity);

    virtual float calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point);
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    void beforeRender() override;
 private:
    float intensity = 1;
 protected:
    constexpr static const float NO_SHADOW = 1.0f;
    constexpr static const float FULL_SHADOW = 0.0f;
    virtual std::string getType();
};

#endif //CRAYG_L