#include "ImageWidget.h"
#include "Logger.h"
#include "image/ColorConversion.h"
#include "image/ImageAlgorithms.h"
#include "image/imageiterators/pixels/ImageIterators.h"

namespace crayg {

ImageWidget::ImageWidget(Image &image, QWidget *parent) : QWidget(parent), image(image) {
    bufferToShow = QImage(image.getWidth(), image.getHeight(), QImage::Format_RGB888);
    bufferToShow.fill(0);
    resize(bufferToShow.size());
}

void ImageWidget::paintEvent(QPaintEvent *event) {
    QPainter qPainter(this);
    qPainter.drawImage(QRect(0, 0, size().width(), size().height()), bufferToShow);
}

void ImageWidget::writeMetadata(ImageMetadata imageMetadata) {
}

void ImageWidget::initialize(ImageSpec imageSpec) {
    Logger::info("imageSpec.regionToRender {}", imageSpec.regionToRender);
    regionToRender = imageSpec.regionToRender;
}

void ImageWidget::writeBucketImageBuffer(std::shared_ptr<BucketImageBuffer> bucketImageBuffer) {
    activeBuckets.erase(bucketImageBuffer->imageBucket);
    updateBufferToShow(bucketImageBuffer->imageBucket);
}

void drawHLine(QImage &image, int x_start, int y_start, int length, int width, const QColor &color) {
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

void drawVLine(QImage &image, int x_start, int y_start, int length, int width, const QColor &color) {
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

void drawBucket(QImage &bufferToShow, const ImageBucket &imageBucket) {
    const int x = imageBucket.getPosition().x;
    const int y = imageBucket.getPosition().y;
    const int CROSS_WIDTH = 1;
    static const QColor color = QColor::fromRgb(255, 255, 255);

    drawHLine(bufferToShow, x, y, imageBucket.getWidth(), CROSS_WIDTH, color);
    drawHLine(bufferToShow, x, y + imageBucket.getHeight() - 1, imageBucket.getWidth(), CROSS_WIDTH, color);

    drawVLine(bufferToShow, x, y, imageBucket.getHeight(), CROSS_WIDTH, color);
    drawVLine(bufferToShow, x + imageBucket.getWidth() - 1, y, imageBucket.getHeight(), CROSS_WIDTH, color);
}

void drawRegionToRenderIfNeeded(QImage &bufferToShow, std::optional<Bounds2di> regionToRender) {
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

void ImageWidget::prepareBucket(const ImageBucket imageBucket) {
    activeBuckets.insert(imageBucket);
    drawBucket(bufferToShow, imageBucket);
    drawRegionToRenderIfNeeded(bufferToShow, regionToRender);
}

void ImageWidget::updateBufferToShow(const ImageBucket &imageBucket) {
    const auto pixelBuffer = image.getChannel(currentChannel);
    if (!pixelBuffer) {
        return;
    }
    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        const Vector2i globalPosition = pixel + imageBucket.getPosition();
        Color color = pixelBuffer->getValue(globalPosition);
        if (ColorConversion::channelNeedsLinearToSRgbConversion(currentChannel)) {
            color = ColorConversion::linearToSRGB(color);
        }
        const auto rgbValues = color.getRgbValues();
        bufferToShow.setPixelColor(
            globalPosition.x, globalPosition.y,
            QColor::fromRgb(std::get<0>(rgbValues), std::get<1>(rgbValues), std::get<2>(rgbValues)));
    }
    update();

    for (auto &bucket : activeBuckets) {
        drawBucket(bufferToShow, bucket);
    }

    drawRegionToRenderIfNeeded(bufferToShow, regionToRender);
}

void ImageWidget::changeChannel(std::string newChannel) {
    currentChannel = newChannel;
    updateBufferToShow({{0, 0}, image.getWidth(), image.getHeight()});
}

void ImageWidget::updateChannel(const std::string channelName) {
    if (channelName != currentChannel) {
        return;
    }
    updateBufferToShow({{0, 0}, image.getWidth(), image.getHeight()});
}

}
