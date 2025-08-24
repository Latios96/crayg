#pragma once

#include "scene/RenderSettings.h"

namespace crayg {

class TileSizeEstimator {
  public:
    explicit TileSizeEstimator(const RenderSettings &renderSettings);
    int estimateTileSize() const;
    int estimateTileSize(int threadCount) const;

  private:
    const RenderSettings &renderSettings;
    static constexpr int MIN_TILE_SIZE = 8;
    static constexpr int MAX_TILE_SIZE = 64;
    static constexpr int TILES_PER_THREAD = 4;
};

}
