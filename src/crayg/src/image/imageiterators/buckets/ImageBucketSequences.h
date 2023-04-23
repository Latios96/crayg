#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_

#include "LineByLineSequence.h"
#include "basics/Bound2d.h"
#include "image/Image.h"
#include "image/ImageBucket.h"
#include <vector>

namespace crayg {

class ImageBucketSequences {
  public:
    template <typename I> static std::vector<ImageBucket> lineByLine(const I &i, int bucketWidth) {
        LineByLineSequence lineByLineSequence({i.getWidth(), i.getHeight()}, bucketWidth);
        return lineByLineSequence.getTiles();
    }
};

}
#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
