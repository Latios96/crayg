#include "NextGenImageWidget.h"
#include <QPainter>

namespace crayg {

void NextGenImageWidget::paintEvent(QPaintEvent *event) {
    QPainter qPainter(this);
    qPainter.drawImage(QRect(0, 0, size().width(), size().height()), displayBuffer);
}

NextGenImageWidget::NextGenImageWidget(QWidget *parent) : QWidget(parent) {
}

void NextGenImageWidget::initBuffer(const Resolution &resolution) {
    displayBuffer = QImage(resolution.getWidth(), resolution.getHeight(), QImage::Format_RGB888);
    displayBuffer.fill(0);
    resize(displayBuffer.size());
}

}