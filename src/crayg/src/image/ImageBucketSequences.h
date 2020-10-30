//
// Created by Jan on 21.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_

#include "Image.h"
#include "ImageBucket.h"
#include <vector>

class ImageBucketSequences {
 public:
    template<typename I>
    static std::vector<ImageBucket> lineByLine(const I &i, int bucketWidth) {
        std::vector<ImageBucket> buckets;

        for (int y = 0; y < i.getHeight(); y += bucketWidth) {
            for (int x = 0; x < i.getWidth(); x += bucketWidth) {
                buckets.emplace_back(x,
                                     y,
                                     fitImage(x, bucketWidth, i.getWidth()),
                                     fitImage(y, bucketWidth, i.getHeight()));
            }
        }

        return buckets;
    }
 private:
    static int fitImage(int pos, int bucketWidth, int dimension);
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
