//
// Created by jan on 30.12.18.
//

#ifndef CRAYG_POINTLIGHTSAMPLER_H
#define CRAYG_POINTLIGHTSAMPLER_H


static const float NO_SHADOW = 1.0f;

static const float FULL_SHADOW = 0.0f;

#include "LightSampler.h"

class PointLightSampler : public LightSampler{
public:
    PointLightSampler(SceneIntersector &sceneIntersector, const Light &light);

    float calculateShadowFactor(const Vector3f &point) override;

private:
    Light light;
};


#endif //CRAYG_POINTLIGHTSAMPLER_H
