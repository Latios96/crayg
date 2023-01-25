#include "ImageWidget.h"
#include "image/ImageIterators.h"
namespace crayg {

ImageWidget::ImageWidget(const Resolution &resolution, QWidget *parent) : QWidget(parent) {
    image = QImage(resolution.getWidth(), resolution.getHeight(), QImage::Format_RGB888);
    image.fill(0);
    resize(image.size());
}
void ImageWidget::paintEvent(QPaintEvent *event) {
    QPainter qPainter(this);
    qPainter.drawImage(QRect(0, 0, size().width(), size().height()), image);
}
void ImageWidget::writeMetadata(ImageMetadata imageMetadata) {

}
void ImageWidget::writeBucketImageBuffer(std::shared_ptr<BucketImageBuffer> bucketImageBuffer) {
    for (auto pixel: ImageIterators::lineByLine(bucketImageBuffer->image)) {
        auto rgbValues = bucketImageBuffer->image.getValue(pixel.x, pixel.y).getRgbValues();

        image.setPixelColor(pixel.x + bucketImageBuffer->imageBucket.getX(),
                            pixel.y + bucketImageBuffer->imageBucket.getY(),
                            QColor::fromRgb(std::get<0>(rgbValues),
                                            std::get<1>(rgbValues),
                                            std::get<2>(rgbValues)));
    }
    update();
}

void drawHLine(QImage &image, int x_start, int y_start, int length, int width) {
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < width; y++) {
            int xPos = x_start + x;
            int yPos = y_start + y;
            if(xPos >= image.width() || yPos >= image.width()){
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
            if(xPos >= image.width() || yPos >= image.width()){
                continue;
            }
            image.setPixelColor(x_start + x, y_start + y, QColor::fromRgb(255, 255, 255));
        }
    }
}

void ImageWidget::prepareBucket(const ImageBucket imageBucket) {
    int x = imageBucket.getX();
    int y = imageBucket.getY();
    int CROSS_LENGTH = 5;
    int CROSS_WIDTH = 1;

    drawHLine(image, x, y, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(image, x + imageBucket.getWidth() - CROSS_LENGTH, y, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(image, x, y + imageBucket.getHeight() - CROSS_WIDTH, CROSS_LENGTH, CROSS_WIDTH);
    drawHLine(image,
              x + imageBucket.getWidth() - CROSS_LENGTH,
              y + imageBucket.getHeight() - CROSS_WIDTH,
              CROSS_LENGTH,
              CROSS_WIDTH);

    drawVLine(image, x, y, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(image, x + imageBucket.getWidth() - CROSS_WIDTH, y, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(image, x, y + imageBucket.getHeight() - CROSS_LENGTH, CROSS_LENGTH, CROSS_WIDTH);
    drawVLine(image,
              x + imageBucket.getWidth() - CROSS_WIDTH,
              y + imageBucket.getHeight() - CROSS_LENGTH,
              CROSS_LENGTH,
              CROSS_WIDTH);

    update();
}

}
