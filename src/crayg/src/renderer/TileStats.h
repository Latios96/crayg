#pragma once

#include "image/ImageTile.h"
#include "outputdrivers/NextGenOutputDriver.h"
#include <chrono>
#include <tbb/concurrent_vector.h>
#include <utils/DtoUtils.h>

namespace crayg {

CRAYG_DTO_2(TileTime, Tile, tile, float, seconds);

class TileStats {
  public:
    void processTileTime(Film &film, const Tile &tile, const std::chrono::steady_clock::time_point &startTime);
    void processTileTimes(NextGenOutputDriver &outputDriver, const Resolution &resolution);

  private:
    tbb::concurrent_vector<TileTime> tileTimes;
};

}
