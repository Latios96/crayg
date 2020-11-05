//
// Created by Jan on 04.11.2020.
//

#include "ImageWidget.h"

ImageWidget::ImageWidget(const Resolution &resolution, QWidget *parent) : QWidget(parent) {
    image = QImage(resolution.getWidth(), resolution.getHeight(), QImage::Format_RGB888);
    image.fill(0);
    resize(image.size());
}
void ImageWidget::paintEvent(QPaintEvent *event) {
    QPainter qPainter(this);
    qPainter.drawImage(0, 0, image);
}
