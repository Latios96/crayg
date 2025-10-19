#pragma once

#include "crayg/foundation/math/geometry/Color.h"

namespace crayg {

class MagmaHeatmap {
  public:
    static Color lookup(float normalized);
};

}
