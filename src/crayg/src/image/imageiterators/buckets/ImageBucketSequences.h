#pragma once

#include "BucketSequenceType.h"
#include "basics/Resolution.h"
#include "image/ImageBucket.h"
#include <vector>

namespace crayg {

class ImageBucketSequences {
  public:
    template <typename I>
    static std::vector<ImageBucket> getSequence(const I &i, int bucketWidth, BucketSequenceType bucketSequenceType) {
        return getSequence(Resolution(i.getWidth(), i.getHeight()), bucketWidth, bucketSequenceType);
    }

    static std::vector<ImageBucket> getSequence(const Resolution &resolution, int bucketWidth,
                                                BucketSequenceType bucketSequenceType);
};

}
