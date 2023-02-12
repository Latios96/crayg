#ifndef CRAYG_IMAGE_H
#define CRAYG_IMAGE_H

#include <ostream>
#include <basics/Resolution.h>
#include "basics/Color.h"
#include "basics/Vector3f.h"
#include "ImageMetadata.h"
#include "PixelPosition.h"
#include "PixelBuffer.h"

namespace crayg {

class Image {

 public:
    Image(int width, int height);
    Image(const Resolution &resolution);
    Image(const Image &image);

    int getWidth() const;
    int getHeight() const;

    void setValue(int x, int y, const Color &color);
    Color getValue(int x, int y) const;

    Resolution getResolution() const;
    ImageMetadata metadata;
    PixelBuffer rgb;
};

}
#endif //CRAYG_IMAGE_H
