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
    virtual float area() const = 0;
    Radiance radiance(const Vector3f &point, const Vector3f &normal) override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_AREALIGHT_H_
