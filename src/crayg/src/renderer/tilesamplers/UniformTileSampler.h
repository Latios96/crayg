#pragma once
#include "TileSampler.h"

namespace crayg {

class UniformTileSampler : public TileSampler {
  public:
    UniformTileSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample);
    void addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const override;
    void sampleTile(const Tile &tile) const override;

  private:
    Color renderPixel(const Vector2i &pixel) const;
};

}
