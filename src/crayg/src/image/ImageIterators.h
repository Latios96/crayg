//
// Created by Jan Honsbrok on 28.10.18.
//

#include "LineByLineIterator.h"

template<typename T>
class IteratorAdapter {
 public:
    IteratorAdapter(const Image &image) : image(image) {}

    T begin() {
        return T(0, 0, image);
    }
    T end() {
        return T(image.getWidth() - 1, image.getHeight() - 1, image);
    }
 private:
    const Image &image;
};

class ImageIterators {
 public:
    static IteratorAdapter<LineByLineIterator> lineByLine(Image &image) {
        return {image};
    }
};