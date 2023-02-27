#include "ImageAlgorithms.h"

namespace crayg {

void ImageAlgorithms::copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image) {
    const bool isContained = bucketIsContainedInImage(bucketImageBuffer.imageBucket, image);

    if (!isContained) {
        return;
    }

    for (auto pixel : ImageIterators::lineByLine(bucketImageBuffer.image)) {
        image.setValue(pixel + bucketImageBuffer.imageBucket.getPosition(), bucketImageBuffer.image.getValue(pixel));
    }
}

bool ImageAlgorithms::bucketIsContainedInImage(const ImageBucket &bucket, Image &image) {
    return bucket.getPosition().x >= 0 && bucket.getPosition().y >= 0 &&
           bucket.getPosition().x + bucket.getWidth() <= image.getWidth() &&
           bucket.getPosition().y + bucket.getHeight() <= image.getHeight();
}

}
