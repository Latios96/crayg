#pragma once
#include "BucketSampler.h"

namespace crayg {

class UniformBucketSampler : public BucketSampler {
  public:
    UniformBucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample);
    void addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const override;
    void sampleBucket(const ImageBucket &imageBucket) const override;

  private:
    Color renderPixel(const Vector2i &pixel) const;
};

}
