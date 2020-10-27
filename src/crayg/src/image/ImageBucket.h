//
// Created by Jan on 21.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_

#include <ostream>
class ImageBucket {
 public:
    const int x, y, width, height;
    ImageBucket(int x, int y, int width, int height);
    bool operator==(const ImageBucket &rhs) const;
    bool operator!=(const ImageBucket &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const ImageBucket &bucket);
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKET_H_
