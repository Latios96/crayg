#include "ImageTile.h"

namespace crayg {

ImageTile::ImageTile(const Vector2i &position, int width, int height)
    : image(Image(width, height)), tile(Tile(position, width, height)) {
}

ImageTile::ImageTile(const Tile &tile) : tile(tile), image(Image(tile.getWidth(), tile.getHeight())) {
}

ImageTile::ImageTile() : image(Image(0, 0)), tile(Tile({0, 0}, 0, 0)) {
}

}
