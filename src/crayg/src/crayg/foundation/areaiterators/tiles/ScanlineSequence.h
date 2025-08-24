#pragma once

#include "TileSequence.h"

namespace crayg {

class ScanlineSequence : public TileSequence {
  public:
    ScanlineSequence(const Resolution &resolution, int tileWidth);
    std::vector<Tile> getTiles() override;

  private:
    int fitImage(int pos, int tileWidth, int dimension);
};

}
