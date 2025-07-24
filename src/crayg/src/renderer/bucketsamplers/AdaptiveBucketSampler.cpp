#include "AdaptiveBucketSampler.h"
#include "image/ImageAlgorithms.h"
#include "image/imageiterators/pixels/ImageIterators.h"
#include "sampling/Random.h"
#include "utils/Heatmap.h"

namespace crayg {

AdaptiveBucketSampler::AdaptiveBucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample,
                                             int samplesPerPass, float maxError)
    : BucketSampler(maxSamples, renderSample), samplesPerPass(samplesPerPass), maxError(maxError) {
}

void AdaptiveBucketSampler::addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const {
    imageSpecBuilder.createRgbFloatChannel("sampleCount");
}

void AdaptiveBucketSampler::sampleBucket(BucketImageBuffer &bucketImageBuffer) const {
    auto fullySampledBuffer = bucketImageBuffer.image.getChannel("rgb");
    auto halfSampledBuffer = PixelBuffer::createRgbFloat(Resolution::deduce(bucketImageBuffer.imageBucket));

    int samplesTaken = 0;
    float error = std::numeric_limits<float>::max();

    while (!shouldTerminate(samplesTaken, error)) {
        error = 0;
        samplesTaken += samplesPerPass;
        for (auto pixel : ImageIterators::lineByLine(bucketImageBuffer.imageBucket)) {
            Color fullySampled = Color::createBlack();
            Color halfSampled = Color::createBlack();

            const auto samplePos = bucketImageBuffer.imageBucket.getPosition() + pixel;
            samplePixel(samplePos, fullySampled, halfSampled);

            fullySampledBuffer->addToPixel(pixel, fullySampled);
            halfSampledBuffer->addToPixel(pixel, halfSampled);

            error += evaluateErrorMetric(fullySampled / static_cast<float>(samplesTaken),
                                         halfSampled / (samplesTaken / 2.f));
        }
        error = error / (bucketImageBuffer.imageBucket.getWidth() * bucketImageBuffer.imageBucket.getHeight());
    }

    divideSampleSumBySampleCount(fullySampledBuffer, samplesTaken);
    drawSampleHeatmap(bucketImageBuffer, samplesTaken);
}

void AdaptiveBucketSampler::drawSampleHeatmap(const BucketImageBuffer &bucketImageBuffer, int samplesTaken) const {
    const float relativeSampleCount =
        static_cast<float>(samplesTaken - samplesPerPass) / static_cast<float>(maxSamples - samplesPerPass);

    ImageAlgorithms::fill(*bucketImageBuffer.image.getChannel("sampleCount"),
                          MagmaHeatmap::lookup(relativeSampleCount));
}

void AdaptiveBucketSampler::samplePixel(const Vector2<int> &samplePos, Color &fullySampled, Color &halfSampled) const {
    for (int i = 0; i < samplesPerPass; i++) {
        const Color &sampleColor = renderSample(Random::randomVector2f() + samplePos);
        fullySampled = fullySampled + sampleColor;
        if (i % 2 == 0) {
            halfSampled = halfSampled + sampleColor;
        }
    }
}

float AdaptiveBucketSampler::evaluateErrorMetric(const Color &fullySampled, const Color &halfSampled) const {
    if (fullySampled.hasNaN() || halfSampled.hasNaN()) {
        return 0;
    }
    if (fullySampled.isBlack()) {
        return 0;
    }
    return (std::abs(fullySampled.r - halfSampled.r) + std::abs(fullySampled.g - halfSampled.g) +
            std::abs(fullySampled.b - halfSampled.b)) /
           std::sqrt(fullySampled.r + fullySampled.g + fullySampled.b);
}

bool AdaptiveBucketSampler::shouldTerminate(int samplesTaken, float error) const {
    if (samplesTaken >= maxSamples) {
        return true;
    }
    if (error < maxError) {
        return true;
    }
    return false;
}

void AdaptiveBucketSampler::divideSampleSumBySampleCount(PixelBuffer *fullySampledBuffer, int samplesTaken) const {
    for (auto pixel : ImageIterators::lineByLine(*fullySampledBuffer)) {
        fullySampledBuffer->dividePixel(pixel, samplesTaken);
    }
}

} // crayg