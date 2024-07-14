#pragma once

#include "BucketSequence.h"

namespace crayg {

class MortonSequence : public BucketSequence {
  public:
    MortonSequence(const Resolution &resolution, int bucketWidth);
    std::vector<ImageBucket> getTiles() override;

  private:
};

} // crayg
