#include "PanAndZoomArea.h"
#include <QWheelEvent>
#include <QScrollBar>

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

    int newScrollValueX = this->newScrollValue(event->position().x(),
                                               oldImageSize.width(),
                                               oldScrollbarValueX,
                                               this->widget()->size().width());
    this->horizontalScrollBar()->setValue(newScrollValueX);
    int newScrollValueY = this->newScrollValue(event->position().y(),
                                               oldImageSize.height(),
                                               oldScrollbarValueY,
                                               this->widget()->size().height());
    this->verticalScrollBar()->setValue(newScrollValueY);
}
int PanAndZoomArea::newScrollValue(float mousePosition, float oldImageSize, int oldScrollbarValue, float newImageSize) {
    const auto absolutePositionInVisibleFrame = mousePosition;
    const auto
        absolutePositionInScaledImage = oldScrollbarValue + absolutePositionInVisibleFrame;
    const auto relativePositionInScaledImage = absolutePositionInScaledImage / oldImageSize;

    const auto absolutePositionInNewlyScaledImage = relativePositionInScaledImage * newImageSize;
    const auto newScrollbarValue = absolutePositionInNewlyScaledImage - absolutePositionInVisibleFrame;
    return static_cast<int>(newScrollbarValue);
}
void PanAndZoomArea::setWidget(QWidget *widget) {
    QScrollArea::setWidget(widget);
    originalSize = widget->size();
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
float ZoomFactor::toPercentage() const {
    return 100.0f * std::pow(2, value);
}
ZoomFactor &ZoomFactor::operator++(int) {
    ++value;
    return *this;
}
ZoomFactor &ZoomFactor::operator--(int) {
    --value;
    return *this;
}
ZoomFactor::ZoomFactor(int value) : value(value) {}
} // crayg