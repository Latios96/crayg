#include "MortonSequence.h"
#include "ScanlineSequence.h"
#include <libmorton/morton.h>

namespace crayg {

MortonSequence::MortonSequence(const Resolution &resolution, int bucketWidth)
    : BucketSequence(resolution, bucketWidth) {
}

std::vector<ImageBucket> MortonSequence::getTiles() {
    ScanlineSequence scanlineSequence(resolution, bucketWidth);
    std::vector<ImageBucket> tiles = scanlineSequence.getTiles();

    std::sort(tiles.begin(), tiles.end(), [](ImageBucket &a, ImageBucket &b) {
        return libmorton::morton2D_64_encode(a.getPosition().x, a.getPosition().y) <
               libmorton::morton2D_64_encode(b.getPosition().x, b.getPosition().y);
    });

    return tiles;
}

}