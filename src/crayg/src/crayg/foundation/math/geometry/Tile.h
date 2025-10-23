#pragma once

#include "Vector2.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class Tile {
  public:
    Tile(const Vector2i &position, int width, int height);
    Tile(const Tile &tile);
    Tile();
    bool operator==(const Tile &rhs) const;
    bool operator!=(const Tile &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Tile &tile);
    Vector2i getPosition() const;
    int getWidth() const;
    int getHeight() const;

  private:
    Vector2i position;
    int width, height;
};

}

namespace std {
template <> struct hash<crayg::Tile> {
    size_t operator()(const crayg::Tile &tile) const;
};
}

template <> struct fmt::formatter<crayg::Tile> : ostream_formatter {};
