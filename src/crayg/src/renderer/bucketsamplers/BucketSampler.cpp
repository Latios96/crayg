#include "BucketSampler.h"

namespace crayg {

BucketSampler::BucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample)
    : film(film), maxSamples(maxSamples), renderSample(renderSample) {
}

void BucketSampler::setFilm(Film &film) {
    this->film = &film;
}
}