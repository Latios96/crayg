#pragma once

#include "AreaLight.h"

namespace crayg {

class RectLight : public AreaLight {
  public:
    RectLight();
    RectLight(const Transform &transform, float intensity, float width, float height);
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;
    float getWidth() const;
    void setWidth(float width);
    float getHeight() const;
    void setHeight(float height);
    Vector3f sampleLightShape() const override;
    std::string getType() override;
    float area() const override;

  private:
    float width = 1;
    float height = 1;

  protected:
};

}
