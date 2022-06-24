#include "TeeOutputDriver.h"

namespace crayg {

void TeeOutputDriver::prepareBucket(const ImageBucket &imageBucket) {
    left.prepareBucket(imageBucket);
    right.prepareBucket(imageBucket);
}
void TeeOutputDriver::writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) {
    left.writeBucketImageBuffer(bucketImageBuffer);
    right.writeBucketImageBuffer(bucketImageBuffer);
}
TeeOutputDriver::TeeOutputDriver(OutputDriver &left, OutputDriver &right) : left(left), right(right) {}

}
