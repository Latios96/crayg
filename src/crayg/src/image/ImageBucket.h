//
// Created by Jan on 21.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_

#include <ostream>
class ImageBucket {
 public:
    ImageBucket(int x, int y, int width, int height);
    ImageBucket(const ImageBucket &imageBucket);
    ImageBucket();
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

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_
