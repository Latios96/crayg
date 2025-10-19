#include "UniformTileSampler.h"
#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "crayg/renderer/SampleAccumulator.h"
#include "crayg/renderer/sampling/Random.h"

namespace crayg {

void UniformTileSampler::addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const {
}

void UniformTileSampler::sampleTile(const Tile &tile) const {
    for (auto pixel : AreaIterators::scanlines(tile)) {
        const auto samplePos = tile.getPosition() + pixel;
        const Color pixelColor = renderPixel(samplePos);
        film->addSample("color", samplePos, pixelColor);
    }
}

Color UniformTileSampler::renderPixel(const Vector2i &pixel) const {
    SampleAccumulator sampleAccumulator;

    for (int i = 0; i < maxSamples; i++) {
        sampleAccumulator.addSample(renderSample(Random::randomVector2f() + pixel));
    }

    return sampleAccumulator.getValue();
}

UniformTileSampler::UniformTileSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample)
    : TileSampler(maxSamples, renderSample) {
}

}