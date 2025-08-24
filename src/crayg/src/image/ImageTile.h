#pragma once

#include "Image.h"
#include "crayg/foundation/math/geometry/Tile.h"

namespace crayg {

struct ImageTile {
  public:
    Tile tile;
    Image image;
    ImageTile();
    ImageTile(const Vector2i &position, int width, int height);
    ImageTile(const Tile &tile);
};

}
