#include "UniformBucketSampler.h"
#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "renderer/SampleAccumulator.h"
#include "sampling/Random.h"

namespace crayg {

void UniformBucketSampler::addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const {
}

void UniformBucketSampler::sampleBucket(const ImageBucket &imageBucket) const {
    for (auto pixel : AreaIterators::scanlines(imageBucket)) {
        const auto samplePos = imageBucket.getPosition() + pixel;
        const Color pixelColor = renderPixel(samplePos);
        film->addSample("color", samplePos, pixelColor);
    }
}

Color UniformBucketSampler::renderPixel(const Vector2i &pixel) const {
    SampleAccumulator sampleAccumulator;

    for (int i = 0; i < maxSamples; i++) {
        sampleAccumulator.addSample(renderSample(Random::randomVector2f() + pixel));
    }

    return sampleAccumulator.getValue();
}

UniformBucketSampler::UniformBucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample)
    : BucketSampler(maxSamples, renderSample) {
}

}