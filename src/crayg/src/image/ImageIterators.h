//
// Created by Jan Honsbrok on 28.10.18.
//

#include "LineByLineIterator.h"

template<typename T, typename I>
class IteratorAdapter {
 public:
    IteratorAdapter(const I &i) : i(i) {}

    T begin() {
        return T(0, 0, i);
    }
    T end() {
        return T(i.getWidth() - 1, i.getHeight() - 1, i);
    }
 private:
    const I &i;
};

class ImageIterators {
 public:
    template<typename I>
    static IteratorAdapter<LineByLineIterator<I>, I> lineByLine(I &i) {
        return {i};
    }
};