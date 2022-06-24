#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_RECTLIGHT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_RECTLIGHT_H_

#include "AreaLight.h"

namespace crayg {

class RectLight : public AreaLight {
 public:
    RectLight();
    RectLight(const Transform &transform, float intensity, float width, float height);
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;
    float getWidth() const;
    void setWidth(float width);
    float getHeight() const;
    void setHeight(float height);
    Vector3f sampleLightShape() const override;
    std::string getType() override;
 private:
    float width = 1;
    float height = 1;
 protected:

};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_RECTLIGHT_H_
