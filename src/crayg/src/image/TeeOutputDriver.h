#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_TEEOUTPUTDRIVER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_TEEOUTPUTDRIVER_H_

#include "OutputDriver.h"

namespace crayg {

class TeeOutputDriver : public OutputDriver {
  public:
    TeeOutputDriver(OutputDriver &left, OutputDriver &right);
    void initialize(const ImageSpec &imageSpec) override;
    void prepareBucket(const ImageBucket &imageBucket) override;
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) override;
    void writeImageMetadata(const ImageMetadata &imageMetadata) override;

  private:
    OutputDriver &left;
    OutputDriver &right;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_TEEOUTPUTDRIVER_H_
