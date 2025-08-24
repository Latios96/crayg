#include "Tile.h"
#include <boost/functional/hash.hpp>
#include <utils/ToStringHelper.h>

namespace crayg {

Tile::Tile(const Vector2i &position, int width, int height) : position(position), width(width), height(height) {
}

bool Tile::operator==(const Tile &rhs) const {
    return position == rhs.position && width == rhs.width && height == rhs.height;
}

bool Tile::operator!=(const Tile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Tile &tile) {
    os << ToStringHelper("Tile")
              .addMember("position", tile.position)
              .addMember("width", tile.width)
              .addMember("height", tile.height)
              .finish();
    return os;
}

Vector2i Tile::getPosition() const {
    return position;
}

const int Tile::getWidth() const {
    return width;
}

const int Tile::getHeight() const {
    return height;
}

Tile::Tile(const Tile &tile) : position(tile.position), width(tile.width), height(tile.height) {
}

Tile::Tile() : position(Vector2i(0, 0)), width(0), height(0) {
}

}

namespace std {
size_t std::hash<crayg::Tile>::operator()(const crayg::Tile &tile) const {
    std::size_t seed = 0;
    boost::hash_combine(seed, tile.getPosition().x);
    boost::hash_combine(seed, tile.getPosition().y);
    boost::hash_combine(seed, tile.getWidth());
    boost::hash_combine(seed, tile.getHeight());
    return seed;
}
};
