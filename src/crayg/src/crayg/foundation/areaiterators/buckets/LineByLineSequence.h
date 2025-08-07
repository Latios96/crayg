#pragma once

#include "BucketSequence.h"

namespace crayg {

class LineByLineSequence : public BucketSequence {
  public:
    LineByLineSequence(const Resolution &resolution, int bucketWidth);
    std::vector<ImageBucket> getTiles() override;

  private:
    int fitImage(int pos, int bucketWidth, int dimension);
};

}
