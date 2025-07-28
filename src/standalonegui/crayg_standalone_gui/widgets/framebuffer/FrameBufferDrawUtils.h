#pragma once
#include "basics/Bound2d.h"
#include "image/ImageBucket.h"
#include <QImage>
#include <optional>

namespace crayg {

class FrameBufferDrawUtils {
  public:
    static void drawBucket(QImage &bufferToShow, const ImageBucket &imageBucket);
    static void drawRegionToRenderIfNeeded(QImage &bufferToShow, std::optional<Bounds2di> regionToRender);
    static void drawHLine(QImage &image, int x_start, int y_start, int length, int width, const QColor &color);
    static void drawVLine(QImage &image, int x_start, int y_start, int length, int width, const QColor &color);
};

}