#pragma once

#include "image/BucketImageBuffer.h"
#include "image/ImageSpec.h"

namespace crayg {

class OutputDriver {
  public:
    virtual void initialize(const ImageSpec &imageSpec) = 0;
    virtual void prepareBucket(const ImageBucket &imageBucket) = 0;
    virtual void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) = 0;
    virtual void updateChannel(const std::string &channelName, PixelBuffer *pixelBuffer) = 0;
    virtual void writeImageMetadata(const ImageMetadata &imageMetadata) = 0;
    virtual ~OutputDriver() = default;
};

}
