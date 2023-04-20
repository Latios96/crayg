#include "ImageAlgorithms.h"

namespace crayg {

void ImageAlgorithms::copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image) {
    const bool isContained = bucketIsContainedInImage(bucketImageBuffer.imageBucket, image);

    if (!isContained) {
        return;
    }
    for (auto &channelView : bucketImageBuffer.image.getChannels()) {
        if (!image.hasChannel(channelView.channelName)) {
            continue;
        }
        auto imageChannel = image.getChannel(channelView.channelName);
        for (auto pixel : ImageIterators::lineByLine(channelView.channelBuffer)) {
            imageChannel->setValue(pixel + bucketImageBuffer.imageBucket.getPosition(),
                                   channelView.channelBuffer.getValue(pixel));
        }
    }
}

bool ImageAlgorithms::bucketIsContainedInImage(const ImageBucket &bucket, Image &image) {
    return bucket.getPosition().x >= 0 && bucket.getPosition().y >= 0 &&
           bucket.getPosition().x + bucket.getWidth() <= image.getWidth() &&
           bucket.getPosition().y + bucket.getHeight() <= image.getHeight();
}

}
