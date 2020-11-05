//
// Created by Jan on 04.11.2020.
//

#include <Logger.h>
#include <image/ImageIterators.h>
#include "ImageWidgetOutputDriver.h"
ImageWidgetOutputDriver::ImageWidgetOutputDriver(ImageWidget &imageWidget) : imageWidget(imageWidget) {}

void ImageWidgetOutputDriver::prepareBucket(const ImageBucket &imageBucket) {
    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        imageWidget.image.setPixelColor(pixel.x + imageBucket.getX(),
                                        pixel.y + imageBucket.getY(),
                                        QColor::fromRgb(255, 255, 255));
    }
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

