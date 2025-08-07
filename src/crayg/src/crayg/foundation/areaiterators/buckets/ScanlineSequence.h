#pragma once

#include "BucketSequence.h"

namespace crayg {

class ScanlineSequence : public BucketSequence {
  public:
    ScanlineSequence(const Resolution &resolution, int bucketWidth);
    std::vector<ImageBucket> getTiles() override;

  private:
    int fitImage(int pos, int bucketWidth, int dimension);
};

}
