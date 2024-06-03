#pragma once
#include "BucketSequence.h"

namespace crayg {

class SpiralSequence : public BucketSequence {
  public:
    SpiralSequence(const Resolution &resolution, int bucketWidth);
    std::vector<ImageBucket> getTiles() override;

  private:
    enum class Direction { DOWN, LEFT, UP, RIGHT };

    void addBucketForCurrentDirectionAndChangeDirection(std::vector<ImageBucket> &buckets,
                                                        SpiralSequence::Direction *currentDirection,
                                                        Vector2i *currentPoint,
                                                        const Vector2i &currentDirectionTransform,
                                                        const Vector2i &newDirectionTransform,
                                                        SpiralSequence::Direction newDirection);

    bool bucketIsPartiallyContained(const Vector2i &currentPoint);

    ImageBucket fitToImage(Vector2i currentPoint);

    SpiralSequence::Direction currentDirection = Direction::DOWN;
    Vector2i currentPoint;
    int spiralSize = 1;
    int iterationsWithSize = 0;
};

} // crayg
