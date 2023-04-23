#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_LINEBYLINESEQUENCE_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_LINEBYLINESEQUENCE_H_

#include "BucketSequence.h"

namespace crayg {

class LineByLineSequence : public BucketSequence {
  public:
    LineByLineSequence(const Resolution &resolution, int bucketWidth);
    std::vector<ImageBucket> getTiles() override;

  private:
    int fitImage(int pos, int bucketWidth, int dimension);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_LINEBYLINESEQUENCE_H_
