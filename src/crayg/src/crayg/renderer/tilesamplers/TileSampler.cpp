#include "TileSampler.h"

namespace crayg {

TileSampler::TileSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample)
    : film(film), maxSamples(maxSamples), renderSample(renderSample) {
}

void TileSampler::setFilm(Film &film) {
    this->film = &film;
}
}