//
// Created by Jan on 20.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_

#include "Light.h"

namespace crayg {

class AreaLight : public Light {
 public:
    float calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) override;
    void serialize(Serializer &serializer) override;
    void deserialize(Deserializer &deserializer) override;
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;
    float getWidth() const;
    void setWidth(float width);
    float getHeight() const;
    void setHeight(float height);
 private:
    float width = 1;
    float height = 1;
 protected:
    std::string getType() override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_
