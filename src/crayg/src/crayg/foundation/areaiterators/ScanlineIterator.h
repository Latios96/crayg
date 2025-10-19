#pragma once

#include "crayg/foundation/math/geometry/Vector2.h"

namespace crayg {

template <typename I> class ScanlineIterator {
  public:
    explicit ScanlineIterator(int lX, int lY, const I &i) : i(i) {
        lastX = lX;
        lastY = lY;
    }

    ScanlineIterator &operator++() {
        if (lastX + 1 < i.getWidth()) {
            lastX++;
        } else {
            lastY++;
            lastX = 0;
        }

        return *this;
    }

    Vector2i operator*() const {
        return {lastX, lastY};
    }

    bool operator!=(const ScanlineIterator &o) const {
        return lastX < i.getWidth() && lastY < i.getHeight();
    };

  private:
    int lastX, lastY;
    const I &i;
};

}
