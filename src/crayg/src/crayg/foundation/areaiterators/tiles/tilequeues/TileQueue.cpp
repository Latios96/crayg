#include "TileQueue.h"
#include "crayg/foundation/logging/Logger.h"

namespace crayg {

TileQueue::TileQueue(const std::function<Vector2i()> &getMousePosition) : getMousePosition(getMousePosition) {
    currentMode = TileFollowMode::FOLLOW_SEQUENCE;
}

void TileQueue::start(std::vector<Tile> &tiles) {
    this->tiles = &tiles;
    currentMode = TileFollowMode::FOLLOW_SEQUENCE;
    modeDelegate = std::make_unique<FollowSequenceTileQueue>(tiles);
}

std::optional<Tile> TileQueue::nextTile() {
    std::lock_guard<std::mutex> lock(delegateMutex);
    return modeDelegate->nextTile();
}

void TileQueue::switchMode() {
    std::lock_guard<std::mutex> lock(delegateMutex);
    switch (currentMode) {
    case TileFollowMode::FOLLOW_MOUSE:
        currentMode = TileFollowMode::FOLLOW_SEQUENCE;
        modeDelegate = std::make_unique<FollowSequenceTileQueue>(*tiles);
        break;
    case TileFollowMode::FOLLOW_SEQUENCE:
        currentMode = TileFollowMode::FOLLOW_MOUSE;
        modeDelegate = std::make_unique<FollowMouseTileQueue>(*tiles, getMousePosition);
        break;
    }
}

TileQueue::TileFollowMode TileQueue::getCurrentMode() const {
    return currentMode;
}

}