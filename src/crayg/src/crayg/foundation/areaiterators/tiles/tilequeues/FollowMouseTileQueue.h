#pragma once

#include "TileQueueMode.h"
#include <functional>

namespace crayg {

class FollowMouseTileQueue : public TileQueueMode {
  public:
    explicit FollowMouseTileQueue(std::vector<Tile> &tiles, const std::function<Vector2i()> &getMousePosition);
    std::optional<Tile> nextTile() override;
    ~FollowMouseTileQueue() override = default;

  private:
    int findNearestTile(const Vector2i &mousePosition);
    const std::function<Vector2i()> getMousePosition;
};

}
