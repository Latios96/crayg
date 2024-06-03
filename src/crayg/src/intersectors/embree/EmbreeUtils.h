#pragma once

#include "basics/Ray.h"
#include <embree3/rtcore_ray.h>

namespace crayg {

class EmbreeUtils {
  public:
    static void createRtcRay(const Ray &ray, RTCRay *rtcRay, float tFar = std::numeric_limits<float>::infinity());
    static void createRTCRayHit(const Ray &ray, RTCRayHit *rtcRayHit,
                                float tFar = std::numeric_limits<float>::infinity());
};

} // crayg
