#include "ImageWidgetOutputDriver.h"
#include <Logger.h>
#include <image/ImageIterators.h>
#include <iostream>

namespace crayg {

ImageWidgetOutputDriver::ImageWidgetOutputDriver(ImageWidget &imageWidget) : imageWidget(imageWidget) {
    QObject::connect(&qtSignalAdapter, &QtSignalAdapter::bucketPrepared, &imageWidget, &ImageWidget::prepareBucket);
    QObject::connect(&qtSignalAdapter, &QtSignalAdapter::bucketImageBufferWritten, &imageWidget,
                     &ImageWidget::writeBucketImageBuffer);
    QObject::connect(&qtSignalAdapter, &QtSignalAdapter::metadataWritten, &imageWidget, &ImageWidget::writeMetadata);
}

void ImageWidgetOutputDriver::initialize(const ImageSpec &imageSpec) {
    qtSignalAdapter.initialize(imageSpec);
}

void ImageWidgetOutputDriver::prepareBucket(const ImageBucket &imageBucket) {
    qtSignalAdapter.prepareBucket(imageBucket);
}

void ImageWidgetOutputDriver::writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) {
    qtSignalAdapter.writeBucketImageBuffer(bucketImageBuffer);
}

void ImageWidgetOutputDriver::writeImageMetadata(const ImageMetadata &imageMetadata) {
    qtSignalAdapter.metadataWritten(imageMetadata);
}

}
