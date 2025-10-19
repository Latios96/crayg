#include "TileStats.h"
#include "crayg/foundation/reporting/Heatmap.h"
#include "crayg/image/ImageAlgorithms.h"

namespace crayg {

void TileStats::processTileTime(Film &film, const Tile &tile, const std::chrono::steady_clock::time_point &startTime) {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto secondsForTile = std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime).count() / 1000.f;

    for (auto tilePos : AreaIterators::scanlines(tile)) {
        const Vector2i pixel = tilePos + tile.getPosition();
        film.addSample("absoluteRenderTime", pixel, Color::createGrey(secondsForTile));
    }

    tileTimes.push_back({tile, secondsForTile});
}

void TileStats::processTileTimes(NextGenOutputDriver &outputDriver, const Resolution &resolution) {
    const TileTime tileWithMaxTime = *std::max_element(tileTimes.begin(), tileTimes.end(),
                                                       [](TileTime &a, TileTime &b) { return a.seconds < b.seconds; });
    const float maxTime = tileWithMaxTime.seconds;

    auto maybeBuffer = outputDriver.getFilm().getBufferVariantPtrByName("relativeRenderTime");
    if (!maybeBuffer) {
        return;
    }

    auto buffer = FilmBufferVariants::getAsValueBufferVariantPtr(*maybeBuffer);

    for (auto &tileTime : tileTimes) {
        float relativeTime = tileTime.seconds / maxTime;
        relativeTime = std::isnan(relativeTime) ? 0 : relativeTime;
        const Color relativeTimeColor = MagmaHeatmap::lookup(relativeTime);
        for (auto pixel : AreaIterators::scanlines(tileTime.tile)) {
            const auto globalPos = tileTime.tile.getPosition() + pixel;
            std::visit([&globalPos, &relativeTimeColor](auto buf) { buf->write(globalPos, relativeTimeColor); },
                       *buffer);
        }
    }

    outputDriver.updateChannel("relativeRenderTime");
}
}