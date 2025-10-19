#pragma once

#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/image/ImageSpec.h"
#include "crayg/image/ImageTile.h"
#include "crayg/image/film/Film.h"

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
