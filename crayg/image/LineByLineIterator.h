//
// Created by Jan Honsbrok on 28.10.18.
//

#ifndef CRAYG_IMAGEITERATOR_H
#define CRAYG_IMAGEITERATOR_H


#include "Image.h"

class LineByLineIterator
{
public:

    explicit LineByLineIterator(int lX, int lY, const Image &image) : image(image) {
        lastX = lX;
        lastY = lY;
    }

    LineByLineIterator& operator++() {
        if (lastX+1<image.getWidth()){
            lastX++;
        }
        else {
            lastY++;
            lastX=0;
        }
        return *this;
    }

    PixelPosition operator*() const { return {lastX, lastY}; }

    bool operator!= (const LineByLineIterator& o) const {
        return o.lastX != lastX || o.lastY != lastY;
    };
private:
    int lastX, lastY;
    const Image& image;
};
template <typename T>
class IteratorAdapter{
public:
    IteratorAdapter(const Image &image) : image(image) {}

    T begin(){
        return T(0,0,image);
    }
    T end(){
        return T(image.getWidth()-1,image.getHeight()-1,image);
    }
private:
    const Image& image;
};
#endif //CRAYG_IMAGEITERATOR_H
