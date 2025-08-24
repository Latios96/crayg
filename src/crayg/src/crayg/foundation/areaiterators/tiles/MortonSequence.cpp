#include "MortonSequence.h"
#include "ScanlineSequence.h"
#include <libmorton/morton.h>

namespace crayg {

MortonSequence::MortonSequence(const Resolution &resolution, int tileWidth) : TileSequence(resolution, tileWidth) {
}

std::vector<Tile> MortonSequence::getTiles() {
    ScanlineSequence scanlineSequence(resolution, tileWidth);
    std::vector<Tile> tiles = scanlineSequence.getTiles();

    std::sort(tiles.begin(), tiles.end(), [](Tile &a, Tile &b) {
        return libmorton::morton2D_64_encode(a.getPosition().x, a.getPosition().y) <
               libmorton::morton2D_64_encode(b.getPosition().x, b.getPosition().y);
    });

    return tiles;
}

}