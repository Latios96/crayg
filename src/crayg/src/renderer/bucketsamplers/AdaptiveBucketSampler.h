#ifndef CRAYG_SRC_CRAYG_SRC_RENDERER_ADAPTIVEBUCKETSAMPLER_H_
#define CRAYG_SRC_CRAYG_SRC_RENDERER_ADAPTIVEBUCKETSAMPLER_H_

#include "BucketSampler.h"
#include "basics/Color.h"
#include "image/BucketImageBuffer.h"
#include "image/ImageSpec.h"

namespace crayg {

// todo check if it would make sense to pass renderSample via template
class AdaptiveBucketSampler : public BucketSampler {
  public:
    AdaptiveBucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample, int samplesPerPass,
                          float maxError);
    void addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const override;
    void sampleBucket(BucketImageBuffer &bucketImageBuffer) const override;
    float evaluateErrorMetric(const Color &fullySampled, const Color &halfSampled) const;
    bool shouldTerminate(int samplesTaken, float error) const;

  private:
    int samplesPerPass;
    float maxError;
    void samplePixel(const Vector2<int> &samplePos, Color &fullySampled, Color &halfSampled) const;
    void divideSampleSumBySampleCount(PixelBuffer *fullySampledBuffer, int samplesTaken) const;
    void drawSampleHeatmap(const BucketImageBuffer &bucketImageBuffer, int samplesTaken) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_RENDERER_ADAPTIVEBUCKETSAMPLER_H_
