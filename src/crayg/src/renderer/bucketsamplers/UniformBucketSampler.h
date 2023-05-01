#ifndef CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_UNIFORMBUCKETSAMPLER_H_
#define CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_UNIFORMBUCKETSAMPLER_H_
#include "BucketSampler.h"

namespace crayg {

class UniformBucketSampler : public BucketSampler {
  public:
    UniformBucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample);
    void addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const override;
    void sampleBucket(BucketImageBuffer &bucketImageBuffer) const override;

  private:
    Color renderPixel(const Vector2i &pixel) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_UNIFORMBUCKETSAMPLER_H_
