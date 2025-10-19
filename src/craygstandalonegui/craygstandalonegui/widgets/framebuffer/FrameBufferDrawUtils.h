#pragma once

// clang-format off
#include <QImage>
// clang-format on

#include "crayg/foundation/math/geometry/Bound2d.h"
#include "crayg/foundation/math/geometry/Tile.h"

#include <optional>

namespace crayg {

class FrameBufferDrawUtils {
  public:
    static void drawTile(QImage &bufferToShow, const Tile &tile);
    static void drawRegionToRenderIfNeeded(QImage &bufferToShow, std::optional<Bounds2di> regionToRender);
    static void drawHLine(QImage &image, int x_start, int y_start, int length, int width, const QColor &color);
    static void drawVLine(QImage &image, int x_start, int y_start, int length, int width, const QColor &color);
};

}