//
// Created by Jan on 21.10.2020.
//

#include "ImageBucket.h"
ImageBucket::ImageBucket(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
bool ImageBucket::operator==(const ImageBucket &rhs) const {
    return x == rhs.x &&
        y == rhs.y &&
        width == rhs.width &&
        height == rhs.height;
}
bool ImageBucket::operator!=(const ImageBucket &rhs) const {
    return !(rhs == *this);
}
std::ostream &operator<<(std::ostream &os, const ImageBucket &bucket) {
    os << "x: " << bucket.x << " y: " << bucket.y << " width: " << bucket.width << " height: " << bucket.height;
    return os;
}
const int ImageBucket::getX() const {
    return x;
}
const int ImageBucket::getY() const {
    return y;
}
const int ImageBucket::getWidth() const {
    return width;
}
const int ImageBucket::getHeight() const {
    return height;
}
