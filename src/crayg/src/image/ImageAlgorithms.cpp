//
// Created by Jan on 29.10.2020.
//

#include "ImageAlgorithms.h"

namespace crayg {

void ImageAlgorithms::copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image) {
    const bool isContained = bucketIsContainedInImage(bucketImageBuffer.imageBucket, image);

    if (!isContained) {
        return;
    }

    for (auto pixel : ImageIterators::lineByLine(bucketImageBuffer.image)) {
        image.setValue(pixel.x + bucketImageBuffer.imageBucket.getX(),
                       pixel.y + bucketImageBuffer.imageBucket.getY(),
                       bucketImageBuffer.image.getValue(pixel.x, pixel.y));
    }
}
bool ImageAlgorithms::bucketIsContainedInImage(const ImageBucket &bucket, Image &image) {
    return bucket.getX() >= 0
        && bucket.getY() >= 0
        && bucket.getX() + bucket.getWidth() <= image.getWidth()
        && bucket.getY() + bucket.getHeight() <= image.getHeight();
}

}
