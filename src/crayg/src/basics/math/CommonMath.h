#pragma once

namespace crayg {

class CommonMath {
  public:
    template <typename T, typename V> static V lerp(T t, V val1, V val2) {
        return val1 * (1 - t) + val2 * t;
    }
};

}
