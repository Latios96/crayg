#include "Image.h"

namespace crayg {

Image::Image(int width, int height) : rgb(PixelBuffer({width, height}, PixelFormat::FLOAT, 3)) {

}

Image::Image(const Resolution &resolution) : rgb(PixelBuffer(resolution, PixelFormat::FLOAT, 3)) {
}

Image::Image(const Image &image) : rgb(image.rgb), metadata(image.metadata) {
}

int Image::getWidth() const {
    return rgb.getWidth();
}

int Image::getHeight() const {
    return rgb.getHeight();
}

void Image::setValue(int x, int y, const Color &color) {
    rgb.setValue({x, y}, color);
}

Color Image::getValue(int x, int y) const {
    return rgb.getValue({x, y});
}

Resolution Image::getResolution() const {
    return {rgb.getWidth(), rgb.getHeight()};
}

}