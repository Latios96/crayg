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

void AdaptiveBucketSampler::sampleBucket(const ImageBucket &imageBucket) const {
    int samplesTaken = 0;
    float error = std::numeric_limits<float>::max();

    while (!shouldTerminate(samplesTaken, error)) {
        error = 0;
        samplesTaken += samplesPerPass;
        for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
            Color fullySampled = Color::createBlack();
            Color halfSampled = Color::createBlack();

            const auto samplePos = imageBucket.getPosition() + pixel;
            samplePixel(samplePos, fullySampled, halfSampled);

            film->addSample("color", samplePos, fullySampled / samplesPerPass);

            error += evaluateErrorMetric(fullySampled / static_cast<float>(samplesTaken),
                                         halfSampled / (samplesTaken / 2.f));
        }
        error = error / (imageBucket.getWidth() * imageBucket.getHeight());
    }

    drawSampleHeatmap(imageBucket, samplesTaken);
}

void AdaptiveBucketSampler::drawSampleHeatmap(const ImageBucket &imageBucket, int samplesTaken) const {
    const float relativeSampleCount =
        static_cast<float>(samplesTaken - samplesPerPass) / static_cast<float>(maxSamples - samplesPerPass);

    for (auto bucketPos : ImageIterators::lineByLine(imageBucket)) {
        const Vector2i pixel = bucketPos + imageBucket.getPosition();
        film->addSample("sampleCount", pixel, MagmaHeatmap::lookup(relativeSampleCount));
    }
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

}