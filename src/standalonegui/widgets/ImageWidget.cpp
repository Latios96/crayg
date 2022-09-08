#include "ImageWidget.h"
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

}
