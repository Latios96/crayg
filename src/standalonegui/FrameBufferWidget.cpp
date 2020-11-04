//
// Created by Jan on 04.11.2020.
//

#include "FrameBufferWidget.h"
void FrameBufferWidget::setupUI() {
    image = QImage(1920, 1080, QImage::Format_RGB16);
    image.load("M:/Pictures/inspiration/220_fightoutside.png");

    auto qLabel = new QLabel();
    qLabel->setPixmap(QPixmap::fromImage(image));

    auto scrollArea = new QScrollArea();
    scrollArea->setWidget(qLabel);
    scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    auto layout = new QVBoxLayout();
    layout->addWidget(scrollArea);
    this->setLayout(layout);

    const QSize availableSize = QGuiApplication::primaryScreen()->availableSize();

    if (image.size().width() > availableSize.width() - 100 &&
        image.size().height() > availableSize.height() - 100) {
        resize(availableSize * 3.0f / 5.0f);
    } else {
        resize(QSize(image.size().width() + 40, image.size().height() + 40));
    }

}
