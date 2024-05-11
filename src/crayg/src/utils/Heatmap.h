#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_HEATMAP_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_HEATMAP_H_

#include "basics/Color.h"

namespace crayg {

class MagmaHeatmap {
  public:
    static Color lookup(float normalized);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_HEATMAP_H_
