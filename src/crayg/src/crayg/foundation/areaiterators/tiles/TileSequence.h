#pragma once
#include "crayg/foundation/math/geometry/Bound2d.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/math/geometry/Tile.h"
#include <vector>

namespace crayg {
class TileSequence {
  public:
    TileSequence(const Resolution &resolution, int tileWidth)
        : resolution(resolution), tileWidth(tileWidth),
          imageBounds(Bounds2di({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1})) {
    }

    virtual std::vector<Tile> getTiles() = 0;

    virtual ~TileSequence() = default;

  protected:
    Resolution resolution;
    int tileWidth;
    Bounds2di imageBounds;
};

}
