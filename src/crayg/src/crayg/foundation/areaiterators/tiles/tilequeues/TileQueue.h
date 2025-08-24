#pragma once

#include "FollowMouseTileQueue.h"
#include "FollowSequenceTileQueue.h"
#include "TileQueueMode.h"
#include "crayg/foundation/math/geometry/Tile.h"
#include <mutex>
#include <optional>
#include <vector>

namespace crayg {

struct TileQueue {
    enum class TileFollowMode { FOLLOW_SEQUENCE, FOLLOW_MOUSE };

    explicit TileQueue(const std::function<Vector2i()> &getMousePosition);
    void start(std::vector<Tile> &tiles);
    std::optional<Tile> nextTile();
    TileFollowMode getCurrentMode() const;
    void switchMode();

  private:
    TileFollowMode currentMode;
    std::unique_ptr<TileQueueMode> modeDelegate;

    std::vector<Tile> *tiles = nullptr;
    const std::function<Vector2i()> &getMousePosition;

    std::mutex delegateMutex;
};

}
