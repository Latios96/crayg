#include "ImageWidget.h"
#include "FrameBufferDrawUtils.h"
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
    regionToRender = imageSpec.regionToRender;
}

void ImageWidget::writeBucketImageBuffer(std::shared_ptr<BucketImageBuffer> bucketImageBuffer) {
    activeBuckets.erase(bucketImageBuffer->imageBucket);
    updateBufferToShow(bucketImageBuffer->imageBucket);
}

void ImageWidget::prepareBucket(const ImageBucket imageBucket) {
    activeBuckets.insert(imageBucket);
    FrameBufferDrawUtils::drawBucket(bufferToShow, imageBucket);
    FrameBufferDrawUtils::drawRegionToRenderIfNeeded(bufferToShow, regionToRender);
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
        FrameBufferDrawUtils::drawBucket(bufferToShow, bucket);
    }

    FrameBufferDrawUtils::drawRegionToRenderIfNeeded(bufferToShow, regionToRender);
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
