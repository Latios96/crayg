//
// Created by Jan Honsbrok on 28.10.18.
//

#ifndef CRAYG_IMAGEITERATOR_H
#define CRAYG_IMAGEITERATOR_H

#include "Image.h"
template<typename I>
class LineByLineIterator {
 public:

    explicit LineByLineIterator(int lX, int lY, const I &i) : i(i) {
        lastX = lX;
        lastY = lY;
    }

    LineByLineIterator &operator++() {
        if (lastX + 1 < i.getWidth()) {
            lastX++;
        } else {
            lastY++;
            lastX = 0;
        }
        return *this;
    }

    PixelPosition operator*() const { return {lastX, lastY}; }

    bool operator!=(const LineByLineIterator &o) const {
        return o.lastX != lastX || o.lastY != lastY;
    };
 private:
    int lastX, lastY;
    const I &i;
};

#endif //CRAYG_IMAGEITERATOR_H
