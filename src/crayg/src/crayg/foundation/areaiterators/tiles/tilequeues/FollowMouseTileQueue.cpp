#include "FollowMouseTileQueue.h"

namespace crayg {
FollowMouseTileQueue::FollowMouseTileQueue(std::vector<Tile> &tiles, const std::function<Vector2i()> &getMousePosition)
    : TileQueueMode(tiles), getMousePosition(getMousePosition) {
}

std::optional<Tile> FollowMouseTileQueue::nextTile() {
    if (tiles.empty()) {
        return std::nullopt;
    }
    const auto mousePosition = getMousePosition();
    const int nearestTileIndex = findNearestTile(mousePosition);
    Tile nearestTile = tiles[nearestTileIndex];
    tiles.erase(tiles.begin() + nearestTileIndex);
    return nearestTile;
}

float squaredDistanceBetween(const Vector2i &mousePosition, const Tile &tile) {
    const Vector2i tileMiddle = tile.getPosition() + Vector2i(tile.getHeight() / 2, tile.getWidth() / 2);
    return (tileMiddle - mousePosition).lengthSquared();
}

int FollowMouseTileQueue::findNearestTile(const Vector2i &mousePosition) {
    float minDistance = std::numeric_limits<float>::max();
    int index = 0;
    for (int i = 0; i < tiles.size(); i++) {
        const float distance = squaredDistanceBetween(mousePosition, tiles[i]);
        if (distance < minDistance) {
            minDistance = distance;
            index = i;
        }
    }
    return index;
}

}