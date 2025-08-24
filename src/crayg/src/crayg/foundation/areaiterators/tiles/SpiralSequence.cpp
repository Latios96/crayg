#include "SpiralSequence.h"

namespace crayg {

SpiralSequence::SpiralSequence(const Resolution &resolution, int tileWidth) : TileSequence(resolution, tileWidth) {
}

std::vector<Tile> SpiralSequence::getTiles() {
    const Vector2i middle = Vector2i(resolution.getWidth(), resolution.getHeight()) / 2;
    const int tileCount = std::ceil(static_cast<float>(resolution.getWidth()) / 2 / tileWidth) * 2 *
                          (std::ceil(static_cast<float>(resolution.getHeight()) / 2 / tileWidth) * 2);
    std::vector<Tile> tiles;
    tiles.reserve(tileCount);
    tiles.emplace_back(Vector2i(middle.x, std::max(0, middle.y - tileWidth)),
                       std::min(resolution.getWidth() - middle.x, tileWidth), std::min(middle.y, tileWidth));

    const Vector2i downTransform = Vector2i(0, tileWidth);
    const Vector2i leftTransform = Vector2i(-tileWidth, 0);
    const Vector2i upTransform = Vector2i(0, -tileWidth);
    const Vector2i rightTransform = Vector2i(tileWidth, 0);

    currentPoint = middle;

    while (tiles.size() < tileCount) {
        switch (currentDirection) {
        case Direction::DOWN:
            addTileForCurrentDirectionAndChangeDirection(tiles, &currentDirection, &currentPoint, downTransform,
                                                         leftTransform, SpiralSequence::Direction::LEFT);
            break;
        case Direction::LEFT:
            addTileForCurrentDirectionAndChangeDirection(tiles, &currentDirection, &currentPoint, leftTransform,
                                                         upTransform, SpiralSequence::Direction::UP);
            break;
        case Direction::UP:
            addTileForCurrentDirectionAndChangeDirection(tiles, &currentDirection, &currentPoint, upTransform,
                                                         rightTransform, SpiralSequence::Direction::RIGHT);
            break;
        case Direction::RIGHT:
            addTileForCurrentDirectionAndChangeDirection(tiles, &currentDirection, &currentPoint, rightTransform,
                                                         downTransform, SpiralSequence::Direction::DOWN);
            break;
        }

        iterationsWithSize++;
        if (iterationsWithSize == 2) {
            iterationsWithSize = 0;
            spiralSize++;
        }
    }
    return tiles;
}

void SpiralSequence::addTileForCurrentDirectionAndChangeDirection(std::vector<Tile> &tiles,
                                                                  SpiralSequence::Direction *currentDirection,
                                                                  Vector2i *currentPoint,
                                                                  const Vector2i &currentDirectionTransform,
                                                                  const Vector2i &newDirectionTransform,
                                                                  SpiralSequence::Direction newDirection) {
    for (int i = 0; i < spiralSize; i++) {
        if (tileIsPartiallyContained(*currentPoint)) {
            tiles.emplace_back(fitToImage(*currentPoint));
        }
        *currentPoint = *currentPoint + currentDirectionTransform;
    }
    *currentPoint = *currentPoint - currentDirectionTransform + newDirectionTransform;
    *currentDirection = newDirection;
}

bool SpiralSequence::tileIsPartiallyContained(const Vector2i &currentPoint) {
    const Vector2i topLeftCorner = currentPoint;
    const Vector2i topRightCorner = currentPoint + Vector2i(tileWidth, 0);
    const Vector2i bottomLeftCorner = currentPoint + Vector2i(0, tileWidth);
    const Vector2i bottomRightCorner = currentPoint + Vector2i(tileWidth, tileWidth);

    const bool topLeftCornerIsContained = imageBounds.contains(topLeftCorner);
    const bool topRightCornerIsContained = imageBounds.contains(topRightCorner);
    const bool bottomLeftCornerIsContained = imageBounds.contains(bottomLeftCorner);
    const bool bottomRightCornerIsContained = imageBounds.contains(bottomRightCorner);
    const bool topRightCornerIsNotOnImageEdge = topRightCorner.x > 0;
    const bool bottomLeftCornerIsNotOnImageEdge = bottomLeftCorner.x > 0 && bottomLeftCorner.y > 0;
    const bool bottomRightCornerIsNotOnImageEdge = bottomRightCorner.x > 0 && bottomRightCorner.y > 0;

    return topLeftCornerIsContained || (topRightCornerIsContained && topRightCornerIsNotOnImageEdge) ||
           (bottomLeftCornerIsContained && bottomLeftCornerIsNotOnImageEdge) ||
           (bottomRightCornerIsContained && bottomRightCornerIsNotOnImageEdge);
}

Tile SpiralSequence::fitToImage(Vector2i currentPoint) {
    int calculatedTileWidth = tileWidth;
    int calculatedTileHeight = tileWidth;

    if (currentPoint.x < 0) {
        calculatedTileWidth = calculatedTileWidth + currentPoint.x;
        currentPoint.x = 0;
    }
    if (currentPoint.y < 0) {
        calculatedTileHeight = calculatedTileHeight + currentPoint.y;
        currentPoint.y = 0;
    }
    if (currentPoint.x + tileWidth > imageBounds.max.x) {
        calculatedTileWidth = imageBounds.max.x - currentPoint.x + 1;
    }
    if (currentPoint.y + tileWidth > imageBounds.max.y) {
        calculatedTileHeight = imageBounds.max.y - currentPoint.y + 1;
    }

    return {currentPoint, calculatedTileWidth, calculatedTileHeight};
}

}