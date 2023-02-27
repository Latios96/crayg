#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEOUTPUTDRIVER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEOUTPUTDRIVER_H_

#include "OutputDriver.h"

namespace crayg {

class ImageOutputDriver : public OutputDriver {
  public:
    ImageOutputDriver(Image &image);
    void initialize(const ImageSpec &imageSpec) override;
    void prepareBucket(const ImageBucket &imageBucket) override;
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) override;
    void writeImageMetadata(const ImageMetadata &imageMetadata) override;
    ~ImageOutputDriver() override;

  private:
    Image &image;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEOUTPUTDRIVER_H_
