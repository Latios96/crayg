//
// Created by Jan on 21.10.2020.
//

#include "ImageBucketSequences.h"
std::vector<ImageBucket> ImageBucketSequences::lineByLine(const Image &image, int bucketWidth) {
    std::vector<ImageBucket> buckets;

    for (int y = 0; y < image.getHeight(); y += bucketWidth) {
        for (int x = 0; x < image.getWidth(); x += bucketWidth) {
            buckets.emplace_back(x,
                                 y,
                                 fitImage(x, bucketWidth, image.getWidth()),
                                 fitImage(y, bucketWidth, image.getHeight()));
        }
    }

    return buckets;
}
int ImageBucketSequences::fitImage(int pos, int bucketWidth, int dimension) {
    if (pos + bucketWidth > dimension) {
        return dimension - pos;
    }
    return bucketWidth;
}
