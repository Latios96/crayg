#pragma once

#include "TileSampler.h"
#include "crayg/scene/RenderSettings.h"
#include <memory>

namespace crayg {

class TileSamplerFactory {
  public:
    static std::unique_ptr<TileSampler> createTileSampler(const RenderSettings &renderSettings,
                                                          const std::function<Color(Vector2f)> &renderSample);
};

}
