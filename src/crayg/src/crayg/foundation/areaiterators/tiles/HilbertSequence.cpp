#include "HilbertSequence.h"
#include "ScanlineSequence.h"

#include <gilbert.h>

namespace crayg {

HilbertSequence::HilbertSequence(const Resolution &resolution, int tileWidth) : TileSequence(resolution, tileWidth) {
}

std::vector<Tile> HilbertSequence::getTiles() {
    ScanlineSequence scanlineSequence(resolution, tileWidth);
    std::vector<Tile> tiles = scanlineSequence.getTiles();

    std::sort(tiles.begin(), tiles.end(), [this](Tile &a, Tile &b) {
        return gilbert_xy2d(a.getPosition().x, a.getPosition().y, resolution.getWidth(), resolution.getHeight()) <
               gilbert_xy2d(b.getPosition().x, b.getPosition().y, resolution.getWidth(), resolution.getHeight());
    });

    return tiles;
}

}