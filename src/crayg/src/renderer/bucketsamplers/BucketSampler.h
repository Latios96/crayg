#pragma once

#include "basics/Color.h"
#include "image/BucketImageBuffer.h"
#include "image/ImageSpec.h"

namespace crayg {

class BucketSampler {
  public:
    BucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample);
    virtual void sampleBucket(BucketImageBuffer &bucketImageBuffer) const = 0;
    virtual void addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const = 0;
    virtual ~BucketSampler() = default;

  protected:
    int maxSamples;
    std::function<Color(Vector2f)> renderSample;
};

}
