//
// Created by Jan on 29.10.2020.
//

#include "ImageAlgorithms.h"
#include "ImageIterators.h"
void ImageAlgorithms::copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image) {
    const bool isContained = bucketIsContainedInImage(bucketImageBuffer.imageBucket, image);

    if (!isContained) {
        return;
    }

    for (auto pixel : ImageIterators::lineByLine(image)) {
        image.setValue(pixel.x + bucketImageBuffer.imageBucket.getX(),
                       pixel.y + bucketImageBuffer.imageBucket.getY(),
                       image.getValue(pixel.x, pixel.y));
    }
}
bool ImageAlgorithms::bucketIsContainedInImage(const ImageBucket &bucket, Image &image) {
    return bucket.getX() >= 0
        && bucket.getY() >= 0
        && bucket.getX() + bucket.getWidth() <= image.getWidth()
        && bucket.getY() + bucket.getHeight() <= image.getHeight();
}
