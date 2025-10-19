#pragma once

#include "crayg/foundation/math/geometry/Vector2.h"
#include "crayg/foundation/math/geometry/Vector3f.h"

namespace crayg {

class Sampling {
  public:
    static Vector3f uniformSampleHemisphere();
    static Vector3f uniformSampleHemisphere(float u, float v);
    static Vector3f uniformSampleSphere();
    static Vector3f uniformSampleSphere(float u, float v);
    static Vector2f concentricSampleDisk();
    static Vector2f concentricSampleDisk(float u, float v);
};

}
