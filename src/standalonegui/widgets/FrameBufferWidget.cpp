#include "FrameBufferWidget.h"
#include "IdConstants.h"
#include "qtcrayg/utils/QtUtils.h"
#include "qtcrayg/widgets/QtWidgetsBuilderDsl.h"
#include <QProgressBar>
#include <QSpacerItem>
#include <QStyle>
#include <QTimer>
#include <QTreeWidget>

#include <boost/algorithm/string.hpp>

namespace crayg {

FrameBufferWidget::FrameBufferWidget(QWidget &imageWidget, QWidget *parent)
    : QWidget(parent), imageWidget(imageWidget), resolution(Resolution()) {
    setupUI();
}

QString formatElapsed(const std::chrono::seconds &elapsed) {
    if (elapsed.count() == 0) {
        return QString("<b>Elapsed:</b> –");
    }
    return qformat("<b>Elapsed:</b> {:%Hh %Mm %Ss}", elapsed);
}

QString formatRemaining(const std::chrono::seconds &remaining) {
    if (remaining.count() == 0) {
        return QString("<b>Remaining:</b> –");
    }
    return qformat("<b>Remaining:</b> {:%Hh %Mm %Ss}", remaining);
}

QString formatEstimatedTotal(const std::chrono::seconds &total) {
    if (total.count() == 0) {
        return QString("<b>Estimated Total:</b> –");
    }
    return qformat("<b>Estimated Total:</b> {:%Hh %Mm %Ss}", total);
}

QLayout *progressBarArea() {
    return inVBox({{[]() {
                       auto previousTask = new QLabel();
                       previousTask->setObjectName(IDs::statusPreviousTask);
                       return previousTask;
                   }},
                   []() {
                       auto progress = new QProgressBar();
                       progress->setValue(50);
                       progress->setAlignment(Qt::AlignCenter);
                       progress->setFormat("");
                       progress->setObjectName(IDs::statusProgressBar);
                       progress->hide();
                       return progress;
                   },
                   inHBox({
                       []() {
                           auto elapsed = new QLabel(formatElapsed(std::chrono::seconds(0)));
                           elapsed->setObjectName(IDs::statusElapsed);
                           elapsed->hide();
                           return elapsed;
                       },
                       addHSpacer(30),
                       []() {
                           auto remaining = new QLabel(formatRemaining(std::chrono::seconds(0)));
                           remaining->setObjectName(IDs::statusRemaining);
                           remaining->hide();
                           return remaining;
                       },
                       addHSpacer(30),
                       []() {
                           auto estimatedTotal = new QLabel(formatRemaining(std::chrono::seconds(0)));
                           estimatedTotal->setObjectName(IDs::statusEstimatedTotal);
                           estimatedTotal->hide();
                           return estimatedTotal;
                       },
                       addHStretch(),
                   })});
}

void FrameBufferWidget::setupUI() {
    this->panAndZoomArea = new PanAndZoomArea();
    this->panAndZoomArea->setWidget(&imageWidget);
    QObject::connect(panAndZoomArea, &PanAndZoomArea::zoomFactorChanged, this, &FrameBufferWidget::setZoomFactor);

    auto overallLayout = inHBox({inVBox({inHBox({
                                             [this]() {
                                                 channelComboBox = new QComboBox();
                                                 channelComboBox->setMinimumWidth(150);
                                                 channelComboBox->setMaximumWidth(150);
                                                 return channelComboBox;
                                             },
                                             [this]() {
                                                 followMouseToggle = new IconToggleButton();
                                                 followMouseToggle->setObjectName("followMouseToggle");
                                                 followMouseToggle->setDisabled(true);
                                                 return followMouseToggle;
                                             },
                                             addHStretch(),
                                         }),
                                         this->panAndZoomArea,
                                         inHBox({addHStretch(), progressBarArea(),
                                                 [this]() {
                                                     metadataButton = new SmallIconToggleButton();
                                                     metadataButton->setObjectName("metadataButton");
                                                     return metadataButton;
                                                 }})}),
                                 [this]() {
                                     imageMetadataWidget = new QTreeWidget(this);
                                     imageMetadataWidget->hide();
                                     imageMetadataWidget->setHeaderHidden(true);
                                     imageMetadataWidget->setColumnCount(2);
                                     imageMetadataWidget->setMaximumWidth(400);
                                     return imageMetadataWidget;
                                 }});

    QObject::connect(channelComboBox, &QComboBox::currentTextChanged,
                     [this](QString text) { emit channelChanged(text.toStdString()); });

    QObject::connect(metadataButton, &QPushButton::clicked,
                     [=](bool checked) { imageMetadataWidget->setHidden(!imageMetadataWidget->isHidden()); });

    this->setLayout(overallLayout);

    statusProgressBar = this->findChild<QProgressBar *>(IDs::statusProgressBar);
    statusElapsed = this->findChild<QLabel *>(IDs::statusElapsed);
    statusRemaining = this->findChild<QLabel *>(IDs::statusRemaining);
    statusEstimatedTotal = this->findChild<QLabel *>(IDs::statusEstimatedTotal);
    statusPreviousTask = this->findChild<QLabel *>(IDs::statusPreviousTask);

    setZoomFactor(ZoomFactor());
    adaptToAvailableSize();
}

void FrameBufferWidget::adaptToAvailableSize() {
    const QSize availableSize = QGuiApplication::primaryScreen()->availableSize();
    if (imageWidget.size().width() > availableSize.width() - 100 &&
        imageWidget.size().height() > availableSize.height() - 100) {
        resize(availableSize * 3.0f / 5.0f);
    } else {
        resize(QSize(imageWidget.size().width() + 40,
                     imageWidget.size().height() + 40 + metadataButton->size().height() + 45));
    }
}

void FrameBufferWidget::setZoomFactor(ZoomFactor zoomFactor) {
    generateWindowTitle();
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
    resolution = imageSpec.resolution;
    generateWindowTitle();
    channelComboBox->clear();
    for (auto &channelSpec : imageSpec.channels) {
        channelComboBox->addItem(QString::fromStdString(channelSpec.name));
        channelComboBox->setItemData(channelComboBox->count() - 1, QString::fromStdString(channelSpec.name),
                                     Qt::ToolTipRole);
    }
}

void FrameBufferWidget::setFilmSpec(FilmSpec filmSpec) {
    resolution = filmSpec.resolution;
    adaptToAvailableSize();
    generateWindowTitle();
    channelComboBox->clear();
    for (auto &channelSpec : filmSpec.channels) {
        channelComboBox->addItem(QString::fromStdString(channelSpec.name));
        channelComboBox->setItemData(channelComboBox->count() - 1, QString::fromStdString(channelSpec.name),
                                     Qt::ToolTipRole);
    }
    channelComboBox->setCurrentIndex(0);
}

void FrameBufferWidget::startTask(BaseTaskReporter::Task task) {
    statusPreviousTask->hide();
    statusProgressBar->setFormat(qformat("{}..", task.name));
    statusProgressBar->setValue(0);
    statusProgressBar->show();
    statusElapsed->show();
    statusElapsed->setText(formatElapsed(std::chrono::seconds(0)));
    statusRemaining->show();
    statusRemaining->setText(formatRemaining(std::chrono::seconds(0)));
    statusEstimatedTotal->show();
    statusEstimatedTotal->setText(formatRemaining(std::chrono::seconds(0)));

    const bool renderingStarted = task.name == "Rendering";
    if (renderingStarted) {
        followMouseToggle->setEnabled(true);
    }
}

void FrameBufferWidget::finishTask(BaseTaskReporter::Task task) {
    statusPreviousTask->show();
    statusPreviousTask->setText(qformat("{} took {:%Hh %Mm %Ss}", task.name, task.elapsedTime()));
    statusProgressBar->hide();
    statusElapsed->hide();
    statusRemaining->hide();
    statusEstimatedTotal->hide();
}

void FrameBufferWidget::updateTask(BaseTaskReporter::Task task) {
    const auto elapsedTime = task.elapsedTime();
    const auto estimatedTimeRemaining = task.estimatedTimeRemaining();
    const auto estimatedTotalTime = elapsedTime + estimatedTimeRemaining;

    statusProgressBar->setValue(task.progress());
    statusElapsed->setText(formatElapsed(elapsedTime));
    statusRemaining->setText(formatRemaining(estimatedTimeRemaining));
    statusEstimatedTotal->setText(formatEstimatedTotal(estimatedTotalTime));
}

void FrameBufferWidget::generateWindowTitle() {
    const auto title = qformat("Crayg Frame Buffer - [{} of {}x{}]", panAndZoomArea->getZoomFactor(),
                               resolution.getWidth(), resolution.getHeight());
    this->setWindowTitle(title);
}

void FrameBufferWidget::connectToggleFollowMouse(const std::function<void()> &toggle) {
    QObject::connect(followMouseToggle, &QCheckBox::toggled, [=](bool checked) { toggle(); });
}

}