#include "BucketSampler.h"

namespace crayg {

BucketSampler::BucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample)
    : maxSamples(std::pow<int>(maxSamples, 2)), renderSample(renderSample) {
}

} // crayg