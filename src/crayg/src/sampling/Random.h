#ifndef CRAYG_SRC_CRAYG_SRC_SAMPLING_RANDOM_H_
#define CRAYG_SRC_CRAYG_SRC_SAMPLING_RANDOM_H_
#include "basics/Vector2.h"

namespace crayg {

class Random {
  public:
    static float random();
    static Vector2f randomVector2f();
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SAMPLING_RANDOM_H_
