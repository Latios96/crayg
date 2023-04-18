#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_

namespace crayg {

class MathUtils {
  public:
    template <typename T, typename V> static V lerp(T t, V val1, V val2) {
        return val1 * (1 - t) + val2 * t;
    }
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_
