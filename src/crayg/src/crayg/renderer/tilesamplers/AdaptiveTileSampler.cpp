#include "AdaptiveTileSampler.h"
#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "crayg/foundation/reporting/Heatmap.h"
#include "crayg/image/ImageAlgorithms.h"
#include "crayg/renderer/sampling/Random.h"

namespace crayg {

AdaptiveTileSampler::AdaptiveTileSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample,
                                         int samplesPerPass, float maxError)
    : TileSampler(maxSamples, renderSample), samplesPerPass(samplesPerPass), maxError(maxError) {
}

void AdaptiveTileSampler::addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const {
    imageSpecBuilder.createRgbFloatChannel("sampleCount");
}

void AdaptiveTileSampler::sampleTile(const Tile &tile) const {
    int samplesTaken = 0;
    float error = std::numeric_limits<float>::max();

    while (!shouldTerminate(samplesTaken, error)) {
        error = 0;
        samplesTaken += samplesPerPass;
        for (auto pixel : AreaIterators::scanlines(tile)) {
            Color fullySampled = Color::createBlack();
            Color halfSampled = Color::createBlack();

            const auto samplePos = tile.getPosition() + pixel;
            samplePixel(samplePos, fullySampled, halfSampled);

            film->addSample("color", samplePos, fullySampled / samplesPerPass);

            error += evaluateErrorMetric(fullySampled / static_cast<float>(samplesTaken),
                                         halfSampled / (samplesTaken / 2.f));
        }
        error = error / (tile.getWidth() * tile.getHeight());
    }

    drawSampleHeatmap(tile, samplesTaken);
}

void AdaptiveTileSampler::drawSampleHeatmap(const Tile &tile, int samplesTaken) const {
    const float relativeSampleCount =
        static_cast<float>(samplesTaken - samplesPerPass) / static_cast<float>(maxSamples - samplesPerPass);

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
    if (samplesTaken >= maxSamples) {
        return true;
    }
    if (error < maxError) {
        return true;
    }
    return false;
}

}