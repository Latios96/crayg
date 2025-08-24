#include "TileSequences.h"

#include "HilbertSequence.h"
#include "MortonSequence.h"
#include "ScanlineSequence.h"
#include "SpiralSequence.h"
#include "utils/Exceptions.h"
#include <fmt/format.h>

namespace crayg {
std::vector<Tile> TileSequences::getSequence(const Resolution &resolution, int tileWidth,
                                             TileSequenceType tileSequenceType) {
    std::unique_ptr<TileSequence> tileSequence = nullptr;
    switch (tileSequenceType) {
    case TileSequenceType::SCANLINE:
        tileSequence = std::make_unique<ScanlineSequence>(resolution, tileWidth);
        break;
    case TileSequenceType::SPIRAL:
        tileSequence = std::make_unique<SpiralSequence>(resolution, tileWidth);
        break;
    case TileSequenceType::MORTON:
        tileSequence = std::make_unique<MortonSequence>(resolution, tileWidth);
        break;
    case TileSequenceType::HILBERT:
        tileSequence = std::make_unique<HilbertSequence>(resolution, tileWidth);
        break;
    default:
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR(R"(Unsupported TileSequenceType : "{}")", tileSequenceType);
    }
    return tileSequence->getTiles();
}
}
