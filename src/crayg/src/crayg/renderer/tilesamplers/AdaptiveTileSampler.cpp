#include "AdaptiveTileSampler.h"
#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "crayg/foundation/containers/Array2d.h"
#include "crayg/foundation/logging/Logger.h"
#include "crayg/foundation/reporting/Heatmap.h"
#include "crayg/image/ImageAlgorithms.h"
#include "crayg/renderer/sampling/Random.h"

namespace crayg {

AdaptiveTileSampler::AdaptiveTileSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample,
                                         int samplesPerPass, float maxError)
    : TileSampler(maxSamples, renderSample), samplesPerPass(samplesPerPass), maxError(maxError),
      minSamples(std::min<int>(std::ceil(16.0f / std::pow(maxError, 0.3f)), maxSamples)) {
    Logger::info("Adaptive sampler will draw at least {} samples per pixel", minSamples);
}

void AdaptiveTileSampler::addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const {
    imageSpecBuilder.createRgbFloatChannel("sampleCount");
}

void AdaptiveTileSampler::sampleTile(const Tile &tile) const {
    int samplesTaken = 0;
    float error = std::numeric_limits<float>::max();

    Array2d<Color> fullySampled(tile.getWidth(), tile.getHeight());
    Array2d<Color> halfSampled(tile.getWidth(), tile.getHeight());

    while (!shouldTerminate(samplesTaken, error)) {
        error = 0;
        samplesTaken += samplesPerPass;
        for (const auto &pixelInTile : AreaIterators::scanlines(tile)) {

            const auto samplePos = tile.getPosition() + pixelInTile;
            samplePixel(samplePos, fullySampled[pixelInTile], halfSampled[pixelInTile]);

            float pixelError = evaluateErrorMetric(fullySampled[pixelInTile] / static_cast<float>(samplesTaken),
                                                   halfSampled[pixelInTile] / (samplesTaken / 2.f));
            error += pixelError;
            film->addSample("pixelError", samplePos, pixelError);
        }
        error = error / (tile.getPixelCount());
    }

    for (const auto &pixelInTile : AreaIterators::scanlines(tile)) {
        const auto samplePos = tile.getPosition() + pixelInTile;
        film->addSample("color", samplePos, fullySampled[pixelInTile] / samplesTaken);
    }

    drawSampleHeatmap(tile, samplesTaken);
}

void AdaptiveTileSampler::drawSampleHeatmap(const Tile &tile, int samplesTaken) const {
    const float relativeSampleCount = static_cast<float>(samplesTaken) / static_cast<float>(maxSamples);

    for (auto tilePos : AreaIterators::scanlines(tile)) {
        const Vector2i pixel = tilePos + tile.getPosition();
        film->addSample("sampleCount", pixel, MagmaHeatmap::lookup(relativeSampleCount));
    }
}

void AdaptiveTileSampler::samplePixel(const Vector2<int> &samplePos, Color &fullySampled, Color &halfSampled) const {
    for (int i = 0; i < samplesPerPass; i++) {
        const Color &sampleColor = renderSample(Random::randomVector2f() + samplePos);
        fullySampled = fullySampled + sampleColor;
        if (i % 2 == 0) {
            halfSampled = halfSampled + sampleColor;
        }
    }
}

float AdaptiveTileSampler::evaluateErrorMetric(const Color &fullySampled, const Color &halfSampled) const {
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

bool AdaptiveTileSampler::shouldTerminate(int samplesTaken, float error) const {
    if (samplesTaken < minSamples) {
        return false;
    }
    if (samplesTaken >= maxSamples) {
        return true;
    }
    if (error < maxError) {
        return true;
    }
    return false;
}

int AdaptiveTileSampler::getMinSamples() const {
    return minSamples;
}

}