//
// Created by Jan on 20.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_

#include "Light.h"

class AreaLight : public Light {
 public:
    float calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) override;
    void serialize(Serializer &serializer) override;
    void deserialize(Deserializer &deserializer) override;
 private:
    float width = 1;
    float height = 1;
 protected:
    std::string getType() override;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_
