#include "ImageOutputDriver.h"
#include "image/ImageAlgorithms.h"
#include "image/ImageMetadata.h"

namespace crayg {

void ImageOutputDriver::initialize(const ImageSpec &imageSpec) {
    image.addChannelsFromSpec(imageSpec);
}

void ImageOutputDriver::prepareBucket(const ImageBucket &imageBucket) {
}

void ImageOutputDriver::writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) {
    ImageAlgorithms::copyBucketImageBufferIntoImage(bucketImageBuffer, image);
}

ImageOutputDriver::ImageOutputDriver(Image &image) : image(image) {
}

void ImageOutputDriver::writeImageMetadata(const ImageMetadata &imageMetadata) {
    image.metadata = imageMetadata;
}

void ImageOutputDriver::updateChannel(const std::string &channelName, PixelBuffer *pixelBuffer) {
    ImageAlgorithms::updateChannel(image, channelName, pixelBuffer);
}

ImageOutputDriver::~ImageOutputDriver() = default;

}