//
// Created by jan on 31.12.18.
//

#include <memory>
#include <scene/Light.h>
#include "LightSampler.h"
#include "PointLightSampler.h"

#ifndef CRAYG_LIGHTSAMPLERFACTORY_H
#define CRAYG_LIGHTSAMPLERFACTORY_H

#endif //CRAYG_LIGHTSAMPLERFACTORY_H

class LightSamplerFactory {
 public:
    static std::shared_ptr<LightSampler> createLightSampler(Light &light, SceneIntersector &intersector) {
        if (light.lightType == POINT_LIGHT) {
            return std::shared_ptr<LightSampler>(new PointLightSampler(intersector, light));
        }
    }
};
