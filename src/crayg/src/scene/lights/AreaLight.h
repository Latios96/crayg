#pragma once

#include "Light.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

class AreaLight : public Light {
  public:
    AreaLight();
    AreaLight(const Transform &transform, float intensity);
    Vector3f getNormal(Vector3f point) override;
    virtual Vector3f sampleLightShape() const = 0;
    virtual float area() const = 0;
    Radiance radiance(const Vector3f &point, const Vector3f &normal) override;
};

}
