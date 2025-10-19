#include "TileSizeEstimator.h"
#include "crayg/foundation/logging/Logger.h"
#include <thread>

namespace crayg {
int TileSizeEstimator::estimateTileSize() const {
    return estimateTileSize(std::thread::hardware_concurrency());
}

int TileSizeEstimator::estimateTileSize(int threadCount) const {
    const int pixelCount = renderSettings.resolution.getWidth() * renderSettings.resolution.getHeight();
    const int estimatedTileSize =
        static_cast<int>(std::sqrt(pixelCount / threadCount)) / TileSizeEstimator::TILES_PER_THREAD;
    const int tileSize =
        std::clamp(estimatedTileSize, TileSizeEstimator::MIN_TILE_SIZE, TileSizeEstimator::MAX_TILE_SIZE);
    Logger::info("Choosing a tile size of {0}x{0} pixels", tileSize);
    return tileSize;
}

TileSizeEstimator::TileSizeEstimator(const RenderSettings &renderSettings) : renderSettings(renderSettings) {
}
}