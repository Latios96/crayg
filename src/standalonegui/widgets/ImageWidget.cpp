#include "ImageWidget.h"
#include "image/ColorConversion.h"
#include "image/ImageAlgorithms.h"
#include "image/ImageIterators.h"

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
}

void ImageWidget::writeBucketImageBuffer(std::shared_ptr<BucketImageBuffer> bucketImageBuffer) {
    activeBuckets.erase(bucketImageBuffer->imageBucket);
    updateBufferToShow(bucketImageBuffer->imageBucket);
}

void drawHLine(QImage &image, int x_start, int y_start, int length, int width) {
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < width; y++) {
            int xPos = x_start + x;
            int yPos = y_start + y;
            if (xPos >= image.width() || yPos >= image.width()) {
                continue;
            }
            image.setPixelColor(xPos, yPos, QColor::fromRgb(255, 255, 255));
        }
    }
}

void drawVLine(QImage &image, int x_start, int y_start, int length, int width) {
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < width; x++) {
            int xPos = x_start + x;
            int yPos = y_start + y;
            if (xPos >= image.width() || yPos >= image.width()) {
                continue;
            }
            image.setPixelColor(x_start + x, y_start + y, QColor::fromRgb(255, 255, 255));
        }
    }
}

void drawBucket(QImage &bufferToShow, const ImageBucket &imageBucket) {
    int x = imageBucket.getPosition().x;
    int y = imageBucket.getPosition().y;
    int CROSS_LENGTH = 5;
    int CROSS_WIDTH = 1;

    drawHLine(bufferToShow, x, y, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(bufferToShow, x + imageBucket.getWidth() - CROSS_LENGTH, y, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(bufferToShow, x, y + imageBucket.getHeight() - CROSS_WIDTH, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(bufferToShow, x + imageBucket.getWidth() - CROSS_LENGTH, y + imageBucket.getHeight() - CROSS_WIDTH,
              CROSS_LENGTH, CROSS_WIDTH);

    drawVLine(bufferToShow, x, y, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(bufferToShow, x + imageBucket.getWidth() - CROSS_WIDTH, y, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(bufferToShow, x, y + imageBucket.getHeight() - CROSS_LENGTH, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(bufferToShow, x + imageBucket.getWidth() - CROSS_WIDTH, y + imageBucket.getHeight() - CROSS_LENGTH,
              CROSS_LENGTH, CROSS_WIDTH);
}

void ImageWidget::prepareBucket(const ImageBucket imageBucket) {
    activeBuckets.insert(imageBucket);
    drawBucket(bufferToShow, imageBucket);
}

void ImageWidget::updateBufferToShow(const ImageBucket &imageBucket) {
    auto pixelBuffer = image.getChannel(currentChannel);
    if (!pixelBuffer) {
        return;
    }
    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        Vector2i globalPosition = pixel + imageBucket.getPosition();
        Color color = pixelBuffer->getValue(globalPosition);
        if (ColorConversion::channelNeedsLinearToSRgbConversion(currentChannel)) {
            color = ColorConversion::linearToSRGB(color);
        }
        auto rgbValues = color.getRgbValues();
        bufferToShow.setPixelColor(
            globalPosition.x, globalPosition.y,
            QColor::fromRgb(std::get<0>(rgbValues), std::get<1>(rgbValues), std::get<2>(rgbValues)));
    }
    update();

    for (auto &bucket : activeBuckets) {
        drawBucket(bufferToShow, bucket);
    }
}

void ImageWidget::changeChannel(std::string newChannel) {
    currentChannel = newChannel;
    updateBufferToShow({{0, 0}, image.getWidth(), image.getHeight()});
}

}
