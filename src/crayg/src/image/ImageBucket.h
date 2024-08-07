#pragma once

#include "basics/Vector2.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class ImageBucket {
  public:
    ImageBucket(const Vector2i &position, int width, int height);
    ImageBucket(const ImageBucket &imageBucket);
    ImageBucket();
    ~ImageBucket() = default;
    bool operator==(const ImageBucket &rhs) const;
    bool operator!=(const ImageBucket &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const ImageBucket &bucket);
    Vector2i getPosition() const;
    const int getWidth() const;
    const int getHeight() const;

  private:
    Vector2i position;
    int width, height;
};

}

namespace std {
template <> struct hash<crayg::ImageBucket> {
    size_t operator()(const crayg::ImageBucket &imageBucket) const;
};
}

template <> struct fmt::formatter<crayg::ImageBucket> : ostream_formatter {};
