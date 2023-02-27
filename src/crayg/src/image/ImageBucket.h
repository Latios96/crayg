#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_

#include <ostream>

namespace crayg {

class ImageBucket {
  public:
    ImageBucket(int x, int y, int width, int height);
    ImageBucket(const ImageBucket &imageBucket);
    ImageBucket();
    ~ImageBucket() = default;
    bool operator==(const ImageBucket &rhs) const;
    bool operator!=(const ImageBucket &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const ImageBucket &bucket);
    const int getX() const;
    const int getY() const;
    const int getWidth() const;
    const int getHeight() const;

  private:
    int x, y, width, height;
};

}

namespace std {
template <> struct hash<crayg::ImageBucket> {
    size_t operator()(const crayg::ImageBucket &imageBucket) const;
};
}

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_
