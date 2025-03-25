#pragma once

#include "BucketSequence.h"

namespace crayg {

class HilbertSequence : public BucketSequence {
  public:
    HilbertSequence(const Resolution &resolution, int bucketWidth);
    std::vector<ImageBucket> getTiles() override;
};

} // crayg
