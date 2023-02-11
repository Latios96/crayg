#ifndef CRAYG_IMAGE_H
#define CRAYG_IMAGE_H

#include <ostream>
#include <basics/Resolution.h>
#include "basics/Color.h"
#include "basics/Vector3f.h"
#include "ImageMetadata.h"
#include "PixelPosition.h"

namespace crayg {

class Image {

 private:
    int width, height;
    float *values;

    int index(int x, int y) const {
        return (x + width * y) * 3;
    }

 public:
    Image(int width, int height);
    Image(const Resolution &resolution);

    Image(const Image &image);

    int getWidth() const;

    int getHeight() const;

    void setValue(int x, int y, const Color &color);

    void setValue(int x, int y, float r, float g, float b);

    Color getValue(int x, int y) const;

    float *getValues() const;

    ~Image() {
        delete[] values;
    }

    Resolution getResolution() const;
    void init(int width, int height);

    ImageMetadata metadata;
};

}
#endif //CRAYG_IMAGE_H
