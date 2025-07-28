#pragma once

#include "basics/Vector2.h"
#include "basics/Vector3f.h"

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
