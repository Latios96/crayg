#pragma once

#include "OutputDriver.h"

namespace crayg {

class ImageOutputDriver : public OutputDriver {
  public:
    ImageOutputDriver(Image &image);
    void initialize(const ImageSpec &imageSpec) override;
    void prepareBucket(const ImageBucket &imageBucket) override;
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) override;
    void updateChannel(const std::string &channelName, PixelBuffer *pixelBuffer) override;
    void writeImageMetadata(const ImageMetadata &imageMetadata) override;
    ~ImageOutputDriver() override;

  private:
    Image &image;
};

}
