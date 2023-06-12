#include "FrameBufferWidget.h"
#include "QtUtils.h"
#include <QProgressBar>
#include <QSpacerItem>
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

    auto topRowLayout = new QHBoxLayout();

    channelComboBox = new QComboBox();
    channelComboBox->setMaximumWidth(150);
    QObject::connect(channelComboBox, &QComboBox::currentTextChanged,
                     [this](QString text) { emit channelChanged(text.toStdString()); });
    topRowLayout->addWidget(channelComboBox, Qt::AlignLeft);
    topRowLayout->addStretch();
    middleLayout->addLayout(topRowLayout);

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
    imageMetadataWidget->hide();
    imageMetadataWidget->setHeaderHidden(true);
    imageMetadataWidget->setColumnCount(2);
    overallLayout->addWidget(imageMetadataWidget);
    QObject::connect(metadataButton, &QPushButton::clicked,
                     [=](bool checked) { imageMetadataWidget->setHidden(!imageMetadataWidget->isHidden()); });

    this->setLayout(overallLayout);

    setZoomFactor(ZoomFactor());

    const QSize availableSize = QGuiApplication::primaryScreen()->availableSize();

    if (imageWidget.size().width() > availableSize.width() - 100 &&
        imageWidget.size().height() > availableSize.height() - 100) {
        resize(availableSize * 3.0f / 5.0f);
    } else {
        resize(QSize(imageWidget.size().width() + 40, imageWidget.size().height() + 40 +
                                                          metadataButton->size().height() +
                                                          topRowLayout->sizeHint().height()));
    }
}

void FrameBufferWidget::setZoomFactor(ZoomFactor zoomFactor) {
    const auto title =
        qformat("Crayg Frame Buffer - [{} of {}x{}]", zoomFactor, this->panAndZoomArea->getOriginalSize().width(),
                this->panAndZoomArea->getOriginalSize().height());
    this->setWindowTitle(title);
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

    for (auto &metadataEntry : imageMetadata) {
        std::vector<std::string> strings;
        boost::split(strings, metadataEntry.first, boost::is_any_of("/"));
        auto currentItem = rootItem;
        for (auto &pathPart : strings) {
            auto possibleMatchingChild = findChildByName(currentItem, QString::fromStdString(pathPart));
            if (possibleMatchingChild != nullptr) {
                currentItem = possibleMatchingChild;
            } else {
                auto item = new QTreeWidgetItem();
                item->setText(0, QString::fromStdString(pathPart));
                if (pathPart.data() == strings[strings.size() - 1].data()) {
                    item->setText(1, qformat("{}", metadataEntry.second));
                }
                item->setTextAlignment(1, Qt::AlignRight);
                currentItem->addChild(item);
                currentItem = item;
            }
        }
    }

    expand(rootItem);

    imageMetadataWidget->resizeColumnToContents(0);
    imageMetadataWidget->resizeColumnToContents(1);
}

void FrameBufferWidget::setImageSpec(ImageSpec imageSpec) {
    channelComboBox->clear();
    for (auto &channelSpec : imageSpec.channels) {
        channelComboBox->addItem(QString::fromStdString(channelSpec.name));
        channelComboBox->setItemData(channelComboBox->count() - 1, QString::fromStdString(channelSpec.name),
                                     Qt::ToolTipRole);
    }
}

}