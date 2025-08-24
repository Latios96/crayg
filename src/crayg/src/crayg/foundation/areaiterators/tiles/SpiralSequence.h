#pragma once
#include "TileSequence.h"

namespace crayg {

class SpiralSequence : public TileSequence {
  public:
    SpiralSequence(const Resolution &resolution, int tileWidth);
    std::vector<Tile> getTiles() override;

  private:
    enum class Direction { DOWN, LEFT, UP, RIGHT };

    void addTileForCurrentDirectionAndChangeDirection(std::vector<Tile> &tiles,
                                                      SpiralSequence::Direction *currentDirection,
                                                      Vector2i *currentPoint, const Vector2i &currentDirectionTransform,
                                                      const Vector2i &newDirectionTransform,
                                                      SpiralSequence::Direction newDirection);

    bool tileIsPartiallyContained(const Vector2i &currentPoint);

    Tile fitToImage(Vector2i currentPoint);

    SpiralSequence::Direction currentDirection = Direction::DOWN;
    Vector2i currentPoint;
    int spiralSize = 1;
    int iterationsWithSize = 0;
};

}
