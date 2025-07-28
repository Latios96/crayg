#include "UniformBucketSampler.h"
#include "image/imageiterators/pixels/ImageIterators.h"
#include "renderer/SampleAccumulator.h"
#include "sampling/Random.h"

namespace crayg {

void UniformBucketSampler::addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const {
}

void UniformBucketSampler::sampleBucket(BucketImageBuffer &bucketImageBuffer) const {
    for (auto pixel : ImageIterators::lineByLine(bucketImageBuffer.image)) {
        const auto samplePos = bucketImageBuffer.imageBucket.getPosition() + pixel;
        const Color pixelColor = renderPixel(samplePos);
        bucketImageBuffer.image.setValue(pixel, pixelColor);
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