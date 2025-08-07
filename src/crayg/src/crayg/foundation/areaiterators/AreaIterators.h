#pragma once

#include "ScanlineIterator.h"

namespace crayg {

template <typename T, typename I> class IteratorAdapter {
  public:
    IteratorAdapter(const I &i) : i(i) {
    }

    T begin() {
        return T(0, 0, i);
    }

    T end() {
        return T(i.getWidth() - 1, i.getHeight() - 1, i);
    }

  private:
    const I &i;
};

class AreaIterators {
  public:
    template <typename I> static IteratorAdapter<ScanlineIterator<I>, I> scanlines(I &i) {
        return {i};
    }
};

}
