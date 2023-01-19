#include "FrameBufferWidget.h"
#include <QStyle>
#include <QTreeWidget>
#include <boost/algorithm/string.hpp>
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
    metadataButton->setFixedSize(QSize(20, 20));
    metadataButtonLayout->addWidget(metadataButton, Qt::AlignRight);
    middleLayout->addLayout(metadataButtonLayout);

    imageMetadataWidget = new QTreeWidget(this);
    imageMetadataWidget->setHeaderHidden(true);
    overallLayout->addWidget(imageMetadataWidget);

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

QTreeWidgetItem *findChildByName(QTreeWidgetItem *item, const QString &name) {
    for (int i = 0; i < item->childCount(); i++) {
        if (item->child(i)->text(0) == name) {
            return item->child(i);
        }
    }
    return nullptr;
}

void expand(QTreeWidgetItem *item) {
    for (int i = 0; i < item->childCount(); i++) {
        expand(item->child(i));
    }
    item->setExpanded(true);
}

void FrameBufferWidget::setImageMetadata(ImageMetadata imageMetadata) {
    auto rootItem = new QTreeWidgetItem(imageMetadataWidget, QStringList("Image Metadata"));
    imageMetadataWidget->insertTopLevelItem(0, rootItem);

    for (auto &metadataEntry: imageMetadata) {
        std::vector<std::string> strings;
        boost::split(strings, metadataEntry.first, boost::is_any_of("/"));
        auto currentItem = rootItem;
        for (auto &pathPart: strings) {
            auto possibleMatchingChild = findChildByName(currentItem, QString::fromStdString(pathPart));
            if (possibleMatchingChild != nullptr) {
                currentItem = possibleMatchingChild;
            } else {
                auto item = new QTreeWidgetItem();
                item->setText(0, QString::fromStdString(pathPart));
                currentItem->addChild(item);
                currentItem = item;
            }
        }
    }

    expand(rootItem);
}

}