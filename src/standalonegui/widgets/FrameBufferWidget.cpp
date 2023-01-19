#include "FrameBufferWidget.h"
#include <QStyle>
#include <QTreeView>

namespace crayg {

void FrameBufferWidget::setupUI() {
    this->panAndZoomArea = new PanAndZoomArea();
    this->panAndZoomArea->setWidget(&imageWidget);
    QObject::connect(panAndZoomArea, &PanAndZoomArea::zoomFactorChanged, this, &FrameBufferWidget::setZoomFactor);

    auto overallLayout = new QHBoxLayout();

    auto middleLayout = new QVBoxLayout();
    overallLayout->addLayout(middleLayout);
    middleLayout->addWidget(this->panAndZoomArea);

    auto metadataButtonLayout = new QHBoxLayout();
    metadataButtonLayout->addStretch();
    metadataButton = new QPushButton();
    const QIcon icon = this->style()->standardIcon(QStyle::SP_FileDialogDetailedView);
    metadataButton->setIcon(icon);
    metadataButton->setFixedSize(QSize(20,20));
    metadataButtonLayout->addWidget(metadataButton, Qt::AlignRight);
    middleLayout->addLayout(metadataButtonLayout);

    this->setLayout(overallLayout);

    setZoomFactor(ZoomFactor());

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
                                          this->panAndZoomArea->getOriginalSize().width(),
                                          this->panAndZoomArea->getOriginalSize().height());
    this->setWindowTitle(QString::fromStdString(title));
}
void FrameBufferWidget::setImageMetadata(ImageMetadata imageMetadata) {
    Logger::info("{}", imageMetadata);
}

}