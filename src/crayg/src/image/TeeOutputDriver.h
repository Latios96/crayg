//
// Created by Jan on 23.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_TEEOUTPUTDRIVER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_TEEOUTPUTDRIVER_H_

#include "OutputDriver.h"

namespace crayg {

class TeeOutputDriver : public OutputDriver {
 public:
    TeeOutputDriver(OutputDriver &left, OutputDriver &right);
    void prepareBucket(const ImageBucket &imageBucket) override;
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) override;
 private:
    OutputDriver &left;
    OutputDriver &right;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_TEEOUTPUTDRIVER_H_
