//
// Created by Jan on 20.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_POINTLIGHT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_POINTLIGHT_H_

#include "Light.h"
class PointLight : public Light {
 public:
    float calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) override;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_POINTLIGHT_H_
