//
// Created by Jan on 21.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_DISKLIGHT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_DISKLIGHT_H_

#include "Light.h"
class DiskLight : public Light {
 public:
    void beforeRender() override;
    void serialize(Serializer &serializer) override;
    void deserialize(Deserializer &deserializer) override;
    float calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) override;
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
 protected:
    std::string getType() override;
 private:
    float radius = 1;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_DISKLIGHT_H_
