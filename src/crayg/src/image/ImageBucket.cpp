#include "ImageBucket.h"
#include <boost/functional/hash.hpp>
#include <utils/ToStringHelper.h>

namespace crayg {

ImageBucket::ImageBucket(const Vector2i &position, int width, int height)
    : position(position), width(width), height(height) {
}

bool ImageBucket::operator==(const ImageBucket &rhs) const {
    return position == rhs.position && width == rhs.width && height == rhs.height;
}

bool ImageBucket::operator!=(const ImageBucket &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const ImageBucket &bucket) {
    os << ToStringHelper("ImageBucket")
              .addMember("position", bucket.position)
              .addMember("width", bucket.width)
              .addMember("height", bucket.height)
              .finish();
    return os;
}

Vector2i ImageBucket::getPosition() const {
    return position;
}

const int ImageBucket::getWidth() const {
    return width;
}

const int ImageBucket::getHeight() const {
    return height;
}

ImageBucket::ImageBucket(const ImageBucket &imageBucket)
    : position(imageBucket.position), width(imageBucket.width), height(imageBucket.height) {
}

ImageBucket::ImageBucket() : position(Vector2i(0, 0)), width(0), height(0) {
}

}

namespace std {
size_t std::hash<crayg::ImageBucket>::operator()(const crayg::ImageBucket &imageBucket) const {
    std::size_t seed = 0;
    boost::hash_combine(seed, imageBucket.getPosition().x);
    boost::hash_combine(seed, imageBucket.getPosition().y);
    boost::hash_combine(seed, imageBucket.getWidth());
    boost::hash_combine(seed, imageBucket.getHeight());
    return seed;
}
};
