//
// Created by jan on 30.12.18.
//

#ifndef CRAYG_LIGHTSAMPLER_H
#define CRAYG_LIGHTSAMPLER_H

#include <foundation/Vector3f.h>
#include <intersectors/SceneIntersector.h>

class LightSampler {
 public:
    LightSampler(SceneIntersector &sceneIntersector);
    /**
     * Caclulates a shadow factor
     * @param point
     * @return shadow factor:
     * 0.0: full shadow
     * 0.5: half in shadow
     * 1.0: no shadow
     */
    virtual float calculateShadowFactor(const Vector3f &point) = 0;

 protected:
    SceneIntersector &sceneIntersector;
};

#endif //CRAYG_LIGHTSAMPLER_H
