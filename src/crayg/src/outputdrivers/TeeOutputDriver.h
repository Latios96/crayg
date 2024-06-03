#pragma once

#include "OutputDriver.h"

namespace crayg {

class TeeOutputDriver : public OutputDriver {
  public:
    TeeOutputDriver(OutputDriver &left, OutputDriver &right);
    void initialize(const ImageSpec &imageSpec) override;
    void prepareBucket(const ImageBucket &imageBucket) override;
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) override;
    void updateChannel(const std::string &channelName, PixelBuffer *pixelBuffer) override;
    void writeImageMetadata(const ImageMetadata &imageMetadata) override;

  private:
    OutputDriver &left;
    OutputDriver &right;
};

}
