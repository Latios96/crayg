#include "ImageOutputDriver.h"
#include "ImageAlgorithms.h"
#include "ImageMetadata.h"

namespace crayg {

void ImageOutputDriver::initialize(const ImageSpec &imageSpec) {
    image.addChannelsFromSpec(imageSpec);
}

void ImageOutputDriver::prepareBucket(const ImageBucket &imageBucket) {

}
void ImageOutputDriver::writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) {
    ImageAlgorithms::copyBucketImageBufferIntoImage(bucketImageBuffer, image);
}
ImageOutputDriver::ImageOutputDriver(Image &image) : image(image) {}

void ImageOutputDriver::writeImageMetadata(const ImageMetadata &imageMetadata) {
    image.metadata = imageMetadata;
}
ImageOutputDriver::~ImageOutputDriver() = default;

}