#pragma once

#include "TileSampler.h"
#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/image/ImageSpec.h"
#include "crayg/image/ImageTile.h"

namespace crayg {

// todo check if it would make sense to pass renderSample via template
class AdaptiveTileSampler : public TileSampler {
  public:
    AdaptiveTileSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample, int samplesPerPass,
                        float maxError);
    void addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const override;
    void sampleTile(const Tile &tile) const override;
    float evaluateErrorMetric(const Color &fullySampled, const Color &halfSampled) const;
    bool shouldTerminate(int samplesTaken, float error) const;

  private:
    int samplesPerPass;
    float maxError;
    void samplePixel(const Vector2<int> &samplePos, Color &fullySampled, Color &halfSampled) const;
    void drawSampleHeatmap(const Tile &tile, int samplesTaken) const;
};

}
