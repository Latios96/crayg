#include "TeeOutputDriver.h"

namespace crayg {

void TeeOutputDriver::initialize(const ImageSpec &imageSpec) {
    left.initialize(imageSpec);
    right.initialize(imageSpec);
}

void TeeOutputDriver::prepareBucket(const ImageBucket &imageBucket) {
    left.prepareBucket(imageBucket);
    right.prepareBucket(imageBucket);
}

void TeeOutputDriver::writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) {
    left.writeBucketImageBuffer(bucketImageBuffer);
    right.writeBucketImageBuffer(bucketImageBuffer);
}

TeeOutputDriver::TeeOutputDriver(OutputDriver &left, OutputDriver &right) : left(left), right(right) {
}

void TeeOutputDriver::writeImageMetadata(const ImageMetadata &imageMetadata) {
    left.writeImageMetadata(imageMetadata);
    right.writeImageMetadata(imageMetadata);
}

}
