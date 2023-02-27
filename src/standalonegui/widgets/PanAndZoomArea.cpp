#include "PanAndZoomArea.h"
#include <QScrollBar>
#include <QWheelEvent>

namespace crayg {

PanAndZoomArea::PanAndZoomArea(QWidget *parent) : QScrollArea(parent) {
    this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    this->setFrameShape(QFrame::NoFrame);
}

void PanAndZoomArea::wheelEvent(QWheelEvent *event) {
    const bool hasZoom = event->angleDelta().y() != 0;
    if (!hasZoom) {
        event->ignore();
    }

    event->accept();

    const bool isZoomIn = event->angleDelta().y() > 0;
    if (isZoomIn) {
        this->zoomFactor++;
    } else {
        this->zoomFactor--;
    }

    emit zoomFactorChanged(this->zoomFactor);

    const auto oldImageSize = this->widget()->size();
    const auto oldScrollbarValueX = this->horizontalScrollBar()->value();
    const auto oldScrollbarValueY = this->verticalScrollBar()->value();

    if (isZoomIn) {
        this->widget()->resize(this->widget()->size() * 2);
    } else {
        this->widget()->resize(this->widget()->size() / 2);
    }

    int newScrollValueX = this->newScrollValue(event->position().x(), oldImageSize.width(), oldScrollbarValueX,
                                               this->widget()->size().width());
    this->horizontalScrollBar()->setValue(newScrollValueX);
    int newScrollValueY = this->newScrollValue(event->position().y(), oldImageSize.height(), oldScrollbarValueY,
                                               this->widget()->size().height());
    this->verticalScrollBar()->setValue(newScrollValueY);
}

int PanAndZoomArea::newScrollValue(float mousePosition, float oldImageSize, int oldScrollbarValue, float newImageSize) {
    const auto absolutePositionInVisibleFrame = mousePosition;
    const auto absolutePositionInScaledImage = oldScrollbarValue + absolutePositionInVisibleFrame;
    const auto relativePositionInScaledImage = absolutePositionInScaledImage / oldImageSize;

    const auto absolutePositionInNewlyScaledImage = relativePositionInScaledImage * newImageSize;
    const auto newScrollbarValue = absolutePositionInNewlyScaledImage - absolutePositionInVisibleFrame;
    return static_cast<int>(newScrollbarValue);
}

void PanAndZoomArea::setWidget(QWidget *widget) {
    QScrollArea::setWidget(widget);
    originalSize = widget->size();
}

void PanAndZoomArea::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        event->accept();
        startMove(event->globalPos());
    }
}

void PanAndZoomArea::mouseMoveEvent(QMouseEvent *event) {
    if (isMoving) {
        applyMove(move(event->globalPos()));
    }
}

void PanAndZoomArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        event->accept();
        applyMove(endMove(event->globalPos()));
    }
}

void PanAndZoomArea::applyMove(const QPoint point) {
    this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + point.x());
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() + point.y());
}

void PanAndZoomArea::startMove(const QPoint &point) {
    isMoving = true;
    panStartPoint = point;
}

QPoint PanAndZoomArea::move(const QPoint &point) {
    const QPoint &offset = panStartPoint - point;
    panStartPoint = point;
    return offset;
}

QPoint PanAndZoomArea::endMove(const QPoint &point) {
    isMoving = false;
    return move(point);
}

const QSize &PanAndZoomArea::getOriginalSize() const {
    return originalSize;
}

void PanAndZoomArea::setOriginalSize(const QSize &originalSize) {
    PanAndZoomArea::originalSize = originalSize;
}

int ZoomFactor::getValue() const {
    return value;
}

bool ZoomFactor::operator==(const ZoomFactor &rhs) const {
    return value == rhs.value;
}

bool ZoomFactor::operator!=(const ZoomFactor &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const ZoomFactor &factor) {
    os << fmt::format("{:.1f}%", factor.toPercentage());
    return os;
}

float ZoomFactor::toFloat() const {
    return 1.0 * std::pow(2, value);
}

float ZoomFactor::toPercentage() const {
    return 100.0f * toFloat();
}

ZoomFactor &ZoomFactor::operator++(int) {
    ++value;
    return *this;
}

ZoomFactor &ZoomFactor::operator--(int) {
    --value;
    return *this;
}

ZoomFactor::ZoomFactor(int value) : value(value) {
}

} // crayg