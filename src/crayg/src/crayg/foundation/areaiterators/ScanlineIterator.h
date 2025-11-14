#pragma once

#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/math/geometry/Vector2.h"

namespace crayg {

class ScanlineIterator {
  public:
    explicit ScanlineIterator(int lX, int lY, const Resolution &resolution) : resolution(resolution) {
        lastX = lX;
        lastY = lY;
    }

    ScanlineIterator &operator++() {
        if (lastX + 1 < resolution.getWidth()) {
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
        return lastX < resolution.getWidth() && lastY < resolution.getHeight();
    };

  private:
    int lastX, lastY;
    Resolution resolution;
};

}
