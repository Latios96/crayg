#pragma once

#include "TileSequence.h"

namespace crayg {

class HilbertSequence : public TileSequence {
  public:
    HilbertSequence(const Resolution &resolution, int tileWidth);
    std::vector<Tile> getTiles() override;
};

}
