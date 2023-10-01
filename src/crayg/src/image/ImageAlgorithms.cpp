#include "ImageAlgorithms.h"

namespace crayg {

void ImageAlgorithms::copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image) {
    copyBucketImageBufferIntoImage(bucketImageBuffer, image, bucketImageBuffer.image.channelNames());
}

bool ImageAlgorithms::bucketIsContainedInImage(const ImageBucket &bucket, Image &image) {
    return bucket.getPosition().x >= 0 && bucket.getPosition().y >= 0 &&
           bucket.getPosition().x + bucket.getWidth() <= image.getWidth() &&
           bucket.getPosition().y + bucket.getHeight() <= image.getHeight();
}

void ImageAlgorithms::copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image,
                                                     const std::vector<std::string> &channelsToUpdate) {
    const bool isContained = bucketIsContainedInImage(bucketImageBuffer.imageBucket, image);

    if (!isContained) {
        return;
    }
    for (const auto &channelName : channelsToUpdate) {
        if (!image.hasChannel(channelName)) {
            continue;
        }
        auto imageChannel = image.getChannel(channelName);
        auto bucketImageBufferChannel = bucketImageBuffer.image.getChannel(channelName);
        for (auto pixel : ImageIterators::lineByLine(*bucketImageBufferChannel)) {
            imageChannel->setValue(pixel + bucketImageBuffer.imageBucket.getPosition(),
                                   bucketImageBufferChannel->getValue(pixel));
        }
    }
}

void ImageAlgorithms::updateChannel(Image &image, const std::string &channelName, PixelBuffer *pixelBuffer) {
    if (!image.hasChannel(channelName)) {
        return;
    }

    auto imageChannel = image.getChannel(channelName);

    for (auto pixel : ImageIterators::lineByLine(*pixelBuffer)) {
        imageChannel->setValue(pixel, pixelBuffer->getValue(pixel));
    }
}

}
