#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_

namespace crayg {

class MathUtils {
  public:
    template <typename T> static T lerp(T t, T val1, T val2) {
        return (1 - t) * val1 + t * val2;
    }
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_BASICS_MATHUTILS_H_
