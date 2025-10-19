#pragma once

#include "TileSequenceType.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/math/geometry/Tile.h"
#include <vector>

namespace crayg {

class TileSequences {
  public:
    template <typename I>
    static std::vector<Tile> getSequence(const I &i, int tileWidth, TileSequenceType tileSequenceType) {
        return getSequence(Resolution(i.getWidth(), i.getHeight()), tileWidth, tileSequenceType);
    }

    static std::vector<Tile> getSequence(const Resolution &resolution, int tileWidth,
                                         TileSequenceType tileSequenceType);
};

}
