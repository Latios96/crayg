#ifndef CRAYG_SRC_CRAYG_SRC_SAMPLING_SAMPLING_H_
#define CRAYG_SRC_CRAYG_SRC_SAMPLING_SAMPLING_H_

#include "basics/Vector3f.h"

namespace crayg {

class Sampling {
  public:
    static Vector3f uniformSampleHemisphere();
    static Vector3f uniformSampleHemisphere(float u, float v);
    static Vector3f uniformSampleSphere();
    static Vector3f uniformSampleSphere(float u, float v);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SAMPLING_SAMPLING_H_
