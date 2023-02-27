#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEUTILS_H_

#include "basics/Ray.h"
#include <embree3/rtcore_ray.h>

namespace crayg {

class EmbreeUtils {
  public:
    static void createRtcRay(const Ray &ray, RTCRay *rtcRay);
    static void createRTCRayHit(const Ray &ray, RTCRayHit *rtcRayHit);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEUTILS_H_
