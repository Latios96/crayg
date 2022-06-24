#include "Image.h"

namespace crayg {

Image::Image(int width, int height) {
    init(width, height);
}
void Image::init(int width, int height) {
    Image::width = width;
    Image::height = height;

    int size = width * height * 3;
    values = new float[size];

    for (int i = 0; i < size; i++) {
        values[i] = 0;
    }
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

void Image::setValue(int x, int y, const Color &color) {
    int index = this->index(x, y);
    values[index] = color.r;
    values[index + 1] = color.g;
    values[index + 2] = color.b;
}

void Image::setValue(int x, int y, float r, float g, float b) {
    int index = this->index(x, y);
    values[index] = r;
    values[index + 1] = g;
    values[index + 2] = b;
}

Color Image::getValue(int x, int y) const {
    int index = this->index(x, y);
    return {values[index], values[index + 1], values[index + 2]};
}

Image::Image(const Image &image) {
    this->width = image.width;
    this->height = image.height;

    int size = width * height * 3;
    values = new float[size];

    for (int i = 0; i < size; i++) {
        values[i] = image.values[i];
    }
}
float *Image::getValues() const {
    return values;
}
Resolution Image::getResolution() const {
    return Resolution(width, height);
}
Image::Image(const Resolution &resolution) {
    init(resolution.getWidth(), resolution.getHeight());
}

PixelPosition::PixelPosition(int x, int y) : x(x), y(y) {}
bool PixelPosition::operator==(const PixelPosition &rhs) const {
    return x == rhs.x &&
        y == rhs.y;
}
bool PixelPosition::operator!=(const PixelPosition &rhs) const {
    return !(rhs == *this);
}
std::ostream &operator<<(std::ostream &os, const PixelPosition &position) {
    os << "x: " << position.x << " y: " << position.y;
    return os;
}

}