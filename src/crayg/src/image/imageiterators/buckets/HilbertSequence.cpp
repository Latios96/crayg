#include "HilbertSequence.h"
#include "LineByLineSequence.h"

#include "gilbert.h"

namespace crayg {

HilbertSequence::HilbertSequence(const Resolution &resolution, int bucketWidth)
    : BucketSequence(resolution, bucketWidth) {
}

std::vector<ImageBucket> HilbertSequence::getTiles() {
    LineByLineSequence lineByLineSequence(resolution, bucketWidth);
    std::vector<ImageBucket> tiles = lineByLineSequence.getTiles();

    std::sort(tiles.begin(), tiles.end(), [this](ImageBucket &a, ImageBucket &b) {
        return gilbert_xy2d(a.getPosition().x, a.getPosition().y,resolution.getWidth(), resolution.getHeight()) <
               gilbert_xy2d(b.getPosition().x, b.getPosition().y,resolution.getWidth(), resolution.getHeight());
    });

    return tiles;
}

} // crayg