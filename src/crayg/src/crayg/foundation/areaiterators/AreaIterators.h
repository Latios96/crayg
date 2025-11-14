#pragma once

#include "ScanlineIterator.h"

namespace crayg {

template <typename T> class IteratorAdapter {
  public:
    IteratorAdapter(const Resolution &resolution) : resolution(resolution) {
    }

    T begin() {
        return T(0, 0, resolution);
    }

    T end() {
        return T(resolution.getWidth() - 1, resolution.getHeight() - 1, resolution);
    }

  private:
    Resolution resolution;
};

class AreaIterators {
  public:
    template <typename I> static IteratorAdapter<ScanlineIterator> scanlines(const I &i) {
        return IteratorAdapter<ScanlineIterator>(Resolution::deduce(i));
    }
};

}
