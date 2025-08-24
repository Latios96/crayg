#include "FrameBufferDrawUtils.h"

namespace crayg {

void FrameBufferDrawUtils::drawTile(QImage &bufferToShow, const Tile &tile) {
    const int x = tile.getPosition().x;
    const int y = tile.getPosition().y;
    const int CROSS_WIDTH = 1;
    static const QColor color = QColor::fromRgb(255, 255, 255);

    drawHLine(bufferToShow, x, y, tile.getWidth(), CROSS_WIDTH, color);
    drawHLine(bufferToShow, x, y + tile.getHeight() - 1, tile.getWidth(), CROSS_WIDTH, color);

    drawVLine(bufferToShow, x, y, tile.getHeight(), CROSS_WIDTH, color);
    drawVLine(bufferToShow, x + tile.getWidth() - 1, y, tile.getHeight(), CROSS_WIDTH, color);
}

void FrameBufferDrawUtils::drawRegionToRenderIfNeeded(QImage &bufferToShow, std::optional<Bounds2di> regionToRender) {
    static const QColor color = QColor::fromRgb(255, 0, 0);
    if (regionToRender) {
        drawHLine(bufferToShow, regionToRender->min.x, regionToRender->min.y, regionToRender->getWidth(), 1, color);
        drawHLine(bufferToShow, regionToRender->min.x, regionToRender->min.y + regionToRender->getHeight() - 1,
                  regionToRender->getWidth(), 1, color);

        drawVLine(bufferToShow, regionToRender->min.x, regionToRender->min.y, regionToRender->getHeight(), 1, color);
        drawVLine(bufferToShow, regionToRender->min.x + regionToRender->getWidth() - 1, regionToRender->min.y,
                  regionToRender->getHeight(), 1, color);
    }
}

void FrameBufferDrawUtils::drawHLine(QImage &image, int x_start, int y_start, int length, int width,
                                     const QColor &color) {
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < width; y++) {
            const int xPos = x_start + x;
            const int yPos = y_start + y;
            if (xPos >= image.width() || yPos >= image.width()) {
                continue;
            }
            image.setPixelColor(xPos, yPos, color);
        }
    }
}

void FrameBufferDrawUtils::drawVLine(QImage &image, int x_start, int y_start, int length, int width,
                                     const QColor &color) {
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < width; x++) {
            int xPos = x_start + x;
            int yPos = y_start + y;
            if (xPos >= image.width() || yPos >= image.width()) {
                continue;
            }
            image.setPixelColor(x_start + x, y_start + y, color);
        }
    }
}
}