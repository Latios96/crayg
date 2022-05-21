//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_

#include "Light.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

class AreaLight : public Light {
 public:
    AreaLight();
    AreaLight(const Transform &transform, float intensity);
    virtual Vector3f sampleLightShape() const = 0;
    float calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) override;

};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_
