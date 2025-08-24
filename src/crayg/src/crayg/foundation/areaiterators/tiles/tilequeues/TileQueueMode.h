#pragma once

#include "crayg/foundation/math/geometry/Tile.h"
#include <optional>
#include <vector>

namespace crayg {

struct TileQueueMode {
    explicit TileQueueMode(std::vector<Tile> &tiles) : tiles(tiles) {
    }

    virtual std::optional<Tile> nextTile() = 0;

    virtual ~TileQueueMode() = default;

  protected:
    std::vector<Tile> &tiles;
};

}
