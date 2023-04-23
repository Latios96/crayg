#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_

#include "basics/Bound2d.h"
#include "image/Image.h"
#include "image/ImageBucket.h"
#include <vector>

namespace crayg {

class ImageBucketSequences {
  public:
    template <typename I> static std::vector<ImageBucket> lineByLine(const I &i, int bucketWidth) {
        std::vector<ImageBucket> buckets;

        for (int y = 0; y < i.getHeight(); y += bucketWidth) {
            for (int x = 0; x < i.getWidth(); x += bucketWidth) {
                buckets.emplace_back(Vector2i(x, y), fitImage(x, bucketWidth, i.getWidth()),
                                     fitImage(y, bucketWidth, i.getHeight()));
            }
        }

        return buckets;
    }

  private:
    static int fitImage(int pos, int bucketWidth, int dimension);
};

class SpiralSequence {
    enum Direction { DOWN, LEFT, UP, RIGHT };

  public:
    SpiralSequence(const Resolution &resolution, int bucketWidth)
        : resolution(resolution), bucketWidth(bucketWidth),
          imageBounds(Bounds2di({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1})) {
    }

    std::vector<ImageBucket> getTiles() {
        const Vector2i middle = Vector2i(resolution.getWidth(), resolution.getHeight()) / 2;
        const int bucketCount = std::ceil(static_cast<float>(resolution.getWidth()) / bucketWidth) *
                                std::ceil(static_cast<float>(resolution.getHeight()) / bucketWidth);
        std::vector<ImageBucket> buckets;
        buckets.reserve(bucketCount);
        buckets.emplace_back(middle - Vector2i(0, bucketWidth), bucketWidth, bucketWidth);

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
                addBucketForCurrentDirectionAndChangeDirection(buckets, &currentDirection, &currentPoint,
                                                               rightTransform, downTransform,
                                                               SpiralSequence::Direction::DOWN);
                break;
            }

            iterationsWithSize++;
            if (iterationsWithSize == 2) {
                iterationsWithSize = 0;
                spiralSize++;
            }
        }
        return buckets;
    };

  private:
    void addBucketForCurrentDirectionAndChangeDirection(std::vector<ImageBucket> &buckets,
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

    bool bucketIsPartiallyContained(const Vector2i &currentPoint) {
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

    ImageBucket fitToImage(Vector2i currentPoint) {
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

    Resolution resolution;
    int bucketWidth;
    Bounds2di imageBounds;
    SpiralSequence::Direction currentDirection = DOWN;
    Vector2i currentPoint;
    int spiralSize = 1;
    int iterationsWithSize = 0;
};

}
#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
