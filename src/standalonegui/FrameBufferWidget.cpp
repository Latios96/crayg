#include "FrameBufferWidget.h"
#include "ImageWidget.h"
#include "PanAndZoomArea.h"

namespace crayg {

void FrameBufferWidget::setupUI() {
    this->setWindowTitle("Crayg Frame Buffer");

    auto scrollArea = new PanAndZoomArea();
    scrollArea->setWidget(&imageWidget);
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

}
