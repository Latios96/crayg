#include "ImageBucket.h"
#include <boost/functional/hash.hpp>
#include <utils/ToStringHelper.h>

namespace crayg {

ImageBucket::ImageBucket(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
}

bool ImageBucket::operator==(const ImageBucket &rhs) const {
    return x == rhs.x && y == rhs.y && width == rhs.width && height == rhs.height;
}

bool ImageBucket::operator!=(const ImageBucket &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const ImageBucket &bucket) {
    os << ToStringHelper("ImageBucket")
              .addMember("x", bucket.x)
              .addMember("y", bucket.y)
              .addMember("width", bucket.width)
              .addMember("height", bucket.height)
              .finish();
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

ImageBucket::ImageBucket(const ImageBucket &imageBucket)
    : x(imageBucket.x), y(imageBucket.y), width(imageBucket.width), height(imageBucket.height) {
}

ImageBucket::ImageBucket() : x(0), y(0), width(0), height(0) {
}

}

namespace std {
size_t std::hash<crayg::ImageBucket>::operator()(const crayg::ImageBucket &imageBucket) const {
    std::size_t seed = 0;
    boost::hash_combine(seed, imageBucket.getX());
    boost::hash_combine(seed, imageBucket.getY());
    boost::hash_combine(seed, imageBucket.getWidth());
    boost::hash_combine(seed, imageBucket.getHeight());
    return seed;
}
};
