#include <Logger.h>
#include <image/ImageIterators.h>
#include <iostream>
#include "ImageWidgetOutputDriver.h"

namespace crayg {

ImageWidgetOutputDriver::ImageWidgetOutputDriver(ImageWidget &imageWidget) : imageWidget(imageWidget) {}

void drawHLine(QImage &image, int x_start, int y_start, int length, int width) {
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < width; y++) {
            image.setPixelColor(x_start + x, y_start + y, QColor::fromRgb(255, 255, 255));
        }
    }
}

void drawVLine(QImage &image, int x_start, int y_start, int length, int width) {
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < width; x++) {
            image.setPixelColor(x_start + x, y_start + y, QColor::fromRgb(255, 255, 255));
        }
    }
}

void ImageWidgetOutputDriver::prepareBucket(const ImageBucket &imageBucket) {
    int x = imageBucket.getX();
    int y = imageBucket.getY();
    int CROSS_LENGTH = 5;
    int CROSS_WIDTH = 1;

    drawHLine(imageWidget.image, x, y, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(imageWidget.image, x + imageBucket.getWidth() - CROSS_LENGTH, y, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(imageWidget.image, x, y + imageBucket.getHeight() - CROSS_WIDTH, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(imageWidget.image,
              x + imageBucket.getWidth() - CROSS_LENGTH,
              y + imageBucket.getHeight() - CROSS_WIDTH,
              CROSS_LENGTH,
              CROSS_WIDTH);

    drawVLine(imageWidget.image, x, y, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(imageWidget.image, x + imageBucket.getWidth() - CROSS_WIDTH, y, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(imageWidget.image, x, y + imageBucket.getHeight() - CROSS_LENGTH, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(imageWidget.image,
              x + imageBucket.getWidth() - CROSS_WIDTH,
              y + imageBucket.getHeight() - CROSS_LENGTH,
              CROSS_LENGTH,
              CROSS_WIDTH);

    imageWidget.update();
}
void ImageWidgetOutputDriver::writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) {
    // copy colors into image
    for (auto pixel : ImageIterators::lineByLine(bucketImageBuffer.image)) {
        auto rgbValues = bucketImageBuffer.image.getValue(pixel.x, pixel.y).getRgbValues();

        imageWidget.image.setPixelColor(pixel.x + bucketImageBuffer.imageBucket.getX(),
                                        pixel.y + bucketImageBuffer.imageBucket.getY(),
                                        QColor::fromRgb(std::get<0>(rgbValues),
                                                        std::get<1>(rgbValues),
                                                        std::get<2>(rgbValues)));
    }
    imageWidget.update();
}

}

