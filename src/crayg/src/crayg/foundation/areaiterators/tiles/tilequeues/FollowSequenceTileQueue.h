#pragma once

#include "TileQueueMode.h"

namespace crayg {

class FollowSequenceTileQueue : public TileQueueMode {
  public:
    explicit FollowSequenceTileQueue(std::vector<Tile> &tiles);
    std::optional<Tile> nextTile() override;
    ~FollowSequenceTileQueue() override;

  private:
    int lastTileIndex = -1;
};

}
