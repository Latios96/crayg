#include "FrameBufferDrawUtils.h"

namespace crayg {

void FrameBufferDrawUtils::drawBucket(QImage &bufferToShow, const ImageBucket &imageBucket) {
    const int x = imageBucket.getPosition().x;
    const int y = imageBucket.getPosition().y;
    const int CROSS_WIDTH = 1;
    static const QColor color = QColor::fromRgb(255, 255, 255);

    drawHLine(bufferToShow, x, y, imageBucket.getWidth(), CROSS_WIDTH, color);
    drawHLine(bufferToShow, x, y + imageBucket.getHeight() - 1, imageBucket.getWidth(), CROSS_WIDTH, color);

    drawVLine(bufferToShow, x, y, imageBucket.getHeight(), CROSS_WIDTH, color);
    drawVLine(bufferToShow, x + imageBucket.getWidth() - 1, y, imageBucket.getHeight(), CROSS_WIDTH, color);
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
} // crayg