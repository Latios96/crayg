#include "FollowSequenceTileQueue.h"

namespace crayg {
FollowSequenceTileQueue::FollowSequenceTileQueue(std::vector<Tile> &tiles) : TileQueueMode(tiles) {
}

std::optional<Tile> FollowSequenceTileQueue::nextTile() {
    if (lastTileIndex >= static_cast<int>(tiles.size()) - 1) {
        return std::nullopt;
    }
    lastTileIndex++;
    return tiles[lastTileIndex];
}

FollowSequenceTileQueue::~FollowSequenceTileQueue() {
    if (tiles.empty()) {
        return;
    }
    if (lastTileIndex < 0) {
        return;
    }
    tiles.erase(tiles.begin(), tiles.begin() + lastTileIndex + 1);
}

}