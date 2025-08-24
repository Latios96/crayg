#include "ScanlineSequence.h"

namespace crayg {

ScanlineSequence::ScanlineSequence(const Resolution &resolution, int tileWidth) : TileSequence(resolution, tileWidth) {
}

std::vector<Tile> ScanlineSequence::getTiles() {
    std::vector<Tile> tiles;

    for (int y = 0; y < resolution.getHeight(); y += tileWidth) {
        for (int x = 0; x < resolution.getWidth(); x += tileWidth) {
            tiles.emplace_back(Vector2i(x, y), fitImage(x, tileWidth, resolution.getWidth()),
                               fitImage(y, tileWidth, resolution.getHeight()));
        }
    }

    return tiles;
}

int ScanlineSequence::fitImage(int pos, int tileWidth, int dimension) {
    if (pos + tileWidth > dimension) {
        return dimension - pos;
    }
    return tileWidth;
}
}