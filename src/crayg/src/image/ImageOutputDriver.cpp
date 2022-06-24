#include "ImageOutputDriver.h"
#include "ImageAlgorithms.h"

namespace crayg {

void ImageOutputDriver::prepareBucket(const ImageBucket &imageBucket) {

}
void ImageOutputDriver::writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) {
    ImageAlgorithms::copyBucketImageBufferIntoImage(bucketImageBuffer, image);
}
ImageOutputDriver::ImageOutputDriver(Image &image) : image(image) {}
ImageOutputDriver::~ImageOutputDriver() = default;

}