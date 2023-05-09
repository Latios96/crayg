#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_

#include "utils/DtoUtils.h"
#include <optional>

namespace crayg {

CRAYG_DTO_2(QuadraticSolutions, float, t0, float, t1);

class MathUtils {
  public:
    template <typename T, typename V> static V lerp(T t, V val1, V val2) {
        return val1 * (1 - t) + val2 * t;
    }

    static std::optional<QuadraticSolutions> solveQuadratic(float a, float b, float c);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_
