#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_

#include "Image.h"
#include "ImageBucket.h"
#include "basics/Bound2d.h"
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
    std::vector<ImageBucket> getTiles(const Resolution &resolution, int bucketWidth) {
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

        Bounds2di imageBounds({0, 0}, {resolution.getWidth() - 1, resolution.getHeight() - 1});
        SpiralSequence::Direction currentDirection = DOWN;
        Vector2i currentPoint = middle;
        int spiralSize = 1;
        int iterationsWithSize = 0;
        while (buckets.size() < bucketCount) {
            switch (currentDirection) {
            case DOWN:
                for (int i = 0; i < spiralSize; i++) {
                    if (bucketIsPartiallyContained(imageBounds, currentPoint,
                                                   bucketWidth)) { //
                        buckets.emplace_back(fitToImage(currentPoint, bucketWidth, imageBounds));
                    }
                    currentPoint = currentPoint + downTransform;
                }
                currentPoint = currentPoint - downTransform + leftTransform;
                currentDirection = LEFT;
                break;
            case LEFT:
                for (int i = 0; i < spiralSize; i++) {
                    if (bucketIsPartiallyContained(imageBounds, currentPoint, bucketWidth)) {
                        buckets.emplace_back(fitToImage(currentPoint, bucketWidth, imageBounds));
                    }
                    currentPoint = currentPoint + leftTransform;
                }
                currentPoint = currentPoint - leftTransform + upTransform;
                currentDirection = UP;
                break;
            case UP:
                for (int i = 0; i < spiralSize; i++) {
                    if (bucketIsPartiallyContained(imageBounds, currentPoint, bucketWidth)) {
                        buckets.emplace_back(fitToImage(currentPoint, bucketWidth, imageBounds));
                    }

                    currentPoint = currentPoint + upTransform;
                }
                currentPoint = currentPoint - upTransform + rightTransform;
                currentDirection = RIGHT;
                break;
            case RIGHT:
                for (int i = 0; i < spiralSize; i++) {
                    if (bucketIsPartiallyContained(imageBounds, currentPoint, bucketWidth)) {
                        buckets.emplace_back(fitToImage(currentPoint, bucketWidth, imageBounds));
                    }
                    currentPoint = currentPoint + rightTransform;
                }
                currentPoint = currentPoint - rightTransform + downTransform;
                currentDirection = DOWN;
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
    bool bucketIsPartiallyContained(const Bounds2di &imageBounds, const Vector2i &currentPoint, int bucketWidth) {
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

    ImageBucket fitToImage(Vector2i currentPoint, int bucketWidth, const Bounds2di &imageBounds) {
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

        return ImageBucket(currentPoint, calculatedBucketWidth, calculatedBucketHeight);
    }
};

}
#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
