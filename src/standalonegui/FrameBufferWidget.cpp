#include "FrameBufferWidget.h"

namespace crayg {

void FrameBufferWidget::setupUI() {
    setZoomFactor(ZoomFactor());

    auto scrollArea = new PanAndZoomArea();
    scrollArea->setWidget(&imageWidget);
    this->connect(scrollArea, &PanAndZoomArea::zoomFactorChanged, this, &FrameBufferWidget::setZoomFactor);
    auto layout = new QVBoxLayout();
    layout->addWidget(scrollArea);
    this->setLayout(layout);

    const QSize availableSize = QGuiApplication::primaryScreen()->availableSize();

    if (imageWidget.size().width() > availableSize.width() - 100 &&
        imageWidget.size().height() > availableSize.height() - 100) {
        resize(availableSize * 3.0f / 5.0f);
    } else {
        resize(QSize(imageWidget.size().width() + 40, imageWidget.size().height() + 40));
    }
}
void FrameBufferWidget::setZoomFactor(ZoomFactor zoomFactor) {
    const std::string title = fmt::format("Crayg Frame Buffer - [{} of {}x{}]",
                                          zoomFactor,
                                          imageWidget.size().width(),
                                          imageWidget.size().height());
    this->setWindowTitle(QString::fromStdString(title));
}

}
