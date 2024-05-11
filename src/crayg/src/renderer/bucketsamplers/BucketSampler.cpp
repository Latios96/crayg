#include "BucketSampler.h"

namespace crayg {

BucketSampler::BucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample)
    : maxSamples(maxSamples), renderSample(renderSample) {
}

} // crayg