//
// Created by Jan on 04.11.2020.
//

#include "FrameBufferWidget.h"
#include "ImageWidget.h"

namespace crayg {

void FrameBufferWidget::setupUI() {
    auto scrollArea = new QScrollArea();
    scrollArea->setWidget(&imageWidget);
    scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
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
