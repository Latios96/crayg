#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_DISKLIGHT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_DISKLIGHT_H_

#include "RectLight.h"

namespace crayg {

class DiskLight : public AreaLight {
  public:
    DiskLight();
    DiskLight(const Transform &transform, float intensity, float radius);
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    float getRadius() const;
    void setRadius(float radius);
    BoundingBox getBounds() const override;
    Vector3f sampleLightShape() const override;
    std::string getType() override;
    float area() const override;

  private:
    float radius = 1;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_DISKLIGHT_H_
