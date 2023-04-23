#include "LineByLineSequence.h"

namespace crayg {

LineByLineSequence::LineByLineSequence(const Resolution &resolution, int bucketWidth)
    : BucketSequence(resolution, bucketWidth) {
}

std::vector<ImageBucket> LineByLineSequence::getTiles() {
    std::vector<ImageBucket> buckets;

    for (int y = 0; y < resolution.getHeight(); y += bucketWidth) {
        for (int x = 0; x < resolution.getWidth(); x += bucketWidth) {
            buckets.emplace_back(Vector2i(x, y), fitImage(x, bucketWidth, resolution.getWidth()),
                                 fitImage(y, bucketWidth, resolution.getHeight()));
        }
    }

    return buckets;
}

int LineByLineSequence::fitImage(int pos, int bucketWidth, int dimension) {
    if (pos + bucketWidth > dimension) {
        return dimension - pos;
    }
    return bucketWidth;
}
} // crayg