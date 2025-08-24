#pragma once

#include "basics/Color.h"
#include "image/ImageSpec.h"
#include "image/ImageTile.h"
#include "image/film/Film.h"

namespace crayg {

class TileSampler {
  public:
    TileSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample);
    virtual void sampleTile(const Tile &tile) const = 0;
    virtual void addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const = 0;
    virtual ~TileSampler() = default;
    void setFilm(Film &film);

  protected:
    Film *film;
    int maxSamples;
    std::function<Color(Vector2f)> renderSample;
};

}
