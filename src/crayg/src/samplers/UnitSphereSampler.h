#ifndef CRAYG_SRC_CRAYG_SRC_SAMPLERS_UNITSPHERESAMPLER_H_
#define CRAYG_SRC_CRAYG_SRC_SAMPLERS_UNITSPHERESAMPLER_H_

#include <basics/Vector3f.h>

namespace crayg {

class UnitSphereSampler {
 public:
    static Vector3f randomPointInside();
};

}
#endif //CRAYG_SRC_CRAYG_SRC_SAMPLERS_UNITSPHERESAMPLER_H_
