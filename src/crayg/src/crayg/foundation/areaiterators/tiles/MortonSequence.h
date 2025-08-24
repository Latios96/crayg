#pragma once

#include "TileSequence.h"

namespace crayg {

class MortonSequence : public TileSequence {
  public:
    MortonSequence(const Resolution &resolution, int tileWidth);
    std::vector<Tile> getTiles() override;
};

}
