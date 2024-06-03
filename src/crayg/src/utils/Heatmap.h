#pragma once

#include "basics/Color.h"

namespace crayg {

class MagmaHeatmap {
  public:
    static Color lookup(float normalized);
};

} // crayg
