#pragma once
#include "basics/Bound2d.h"
#include "basics/Resolution.h"
#include "image/ImageBucket.h"
#include <vector>

namespace crayg {
class BucketSequence {
  public:
    BucketSequence(const Resolution &resolution, int bucketWidth)
        : resolution(resolution), bucketWidth(bucketWidth),
          imageBounds(Bounds2di({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1})) {
    }

    virtual std::vector<ImageBucket> getTiles() = 0;

    virtual ~BucketSequence() = default;

  protected:
    Resolution resolution;
    int bucketWidth;
    Bounds2di imageBounds;
};

}
