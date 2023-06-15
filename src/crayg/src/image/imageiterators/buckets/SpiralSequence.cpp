#include "SpiralSequence.h"

namespace crayg {

SpiralSequence::SpiralSequence(const Resolution &resolution, int bucketWidth)
    : BucketSequence(resolution, bucketWidth) {
}

std::vector<ImageBucket> SpiralSequence::getTiles() {
    const Vector2i middle = Vector2i(resolution.getWidth(), resolution.getHeight()) / 2;
    const int bucketCount = std::ceil(static_cast<float>(resolution.getWidth()) / 2 / bucketWidth) * 2 *
                            (std::ceil(static_cast<float>(resolution.getHeight()) / 2 / bucketWidth) * 2);
    std::vector<ImageBucket> buckets;
    buckets.reserve(bucketCount);
    buckets.emplace_back(Vector2i(middle.x, std::max(0, middle.y - bucketWidth)),
                         std::min(resolution.getWidth() - middle.x, bucketWidth), std::min(middle.y, bucketWidth));

    const Vector2i downTransform = Vector2i(0, bucketWidth);
    const Vector2i leftTransform = Vector2i(-bucketWidth, 0);
    const Vector2i upTransform = Vector2i(0, -bucketWidth);
    const Vector2i rightTransform = Vector2i(bucketWidth, 0);

    currentPoint = middle;

    while (buckets.size() < bucketCount) {
        switch (currentDirection) {
        case DOWN:
            addBucketForCurrentDirectionAndChangeDirection(buckets, &currentDirection, &currentPoint, downTransform,
                                                           leftTransform, SpiralSequence::Direction::LEFT);
            break;
        case LEFT:
            addBucketForCurrentDirectionAndChangeDirection(buckets, &currentDirection, &currentPoint, leftTransform,
                                                           upTransform, SpiralSequence::Direction::UP);
            break;
        case UP:
            addBucketForCurrentDirectionAndChangeDirection(buckets, &currentDirection, &currentPoint, upTransform,
                                                           rightTransform, SpiralSequence::Direction::RIGHT);
            break;
        case RIGHT:
            addBucketForCurrentDirectionAndChangeDirection(buckets, &currentDirection, &currentPoint, rightTransform,
                                                           downTransform, SpiralSequence::Direction::DOWN);
            break;
        }

        iterationsWithSize++;
        if (iterationsWithSize == 2) {
            iterationsWithSize = 0;
            spiralSize++;
        }
    }
    return buckets;
}

void SpiralSequence::addBucketForCurrentDirectionAndChangeDirection(std::vector<ImageBucket> &buckets,
                                                                    SpiralSequence::Direction *currentDirection,
                                                                    Vector2i *currentPoint,
                                                                    const Vector2i &currentDirectionTransform,
                                                                    const Vector2i &newDirectionTransform,
                                                                    SpiralSequence::Direction newDirection) {
    for (int i = 0; i < spiralSize; i++) {
        if (bucketIsPartiallyContained(*currentPoint)) {
            buckets.emplace_back(fitToImage(*currentPoint));
        }
        *currentPoint = *currentPoint + currentDirectionTransform;
    }
    *currentPoint = *currentPoint - currentDirectionTransform + newDirectionTransform;
    *currentDirection = newDirection;
}

bool SpiralSequence::bucketIsPartiallyContained(const Vector2i &currentPoint) {
    const Vector2i topLeftCorner = currentPoint;
    const Vector2i topRightCorner = currentPoint + Vector2i(bucketWidth, 0);
    const Vector2i bottomLeftCorner = currentPoint + Vector2i(0, bucketWidth);
    const Vector2i bottomRightCorner = currentPoint + Vector2i(bucketWidth, bucketWidth);

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

ImageBucket SpiralSequence::fitToImage(Vector2i currentPoint) {
    int calculatedBucketWidth = bucketWidth;
    int calculatedBucketHeight = bucketWidth;

    if (currentPoint.x < 0) {
        calculatedBucketWidth = calculatedBucketWidth + currentPoint.x;
        currentPoint.x = 0;
    }
    if (currentPoint.y < 0) {
        calculatedBucketHeight = calculatedBucketHeight + currentPoint.y;
        currentPoint.y = 0;
    }
    if (currentPoint.x + bucketWidth > imageBounds.max.x) {
        calculatedBucketWidth = imageBounds.max.x - currentPoint.x + 1;
    }
    if (currentPoint.y + bucketWidth > imageBounds.max.y) {
        calculatedBucketHeight = imageBounds.max.y - currentPoint.y + 1;
    }

    return {currentPoint, calculatedBucketWidth, calculatedBucketHeight};
}

} // crayg