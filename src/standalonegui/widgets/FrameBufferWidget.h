#pragma once

#include "PanAndZoomArea.h"
#include "image/ImageMetadata.h"
#include "image/ImageSpec.h"
#include "qtcrayg/widgets/IconToggleButton.h"
#include "utils/TaskReporter.h"
#include <QGuiApplication>
#include <QProgressBar>
#include <QScreen>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qscrollarea.h>
#include <fmt/format.h>
#include <iostream>

namespace crayg {

class FrameBufferWidget : public QWidget {
    Q_OBJECT
  public:
    FrameBufferWidget(QWidget &imageWidget, QWidget *parent = nullptr);

    void connectToggleFollowMouse(const std::function<void()> &toggle);

    ~FrameBufferWidget() override = default;
  public slots:
    void setZoomFactor(ZoomFactor zoomFactor);
    void setImageMetadata(ImageMetadata imageMetadata);
    void setImageSpec(ImageSpec imageSpec);
    void startTask(BaseTaskReporter::Task task);
    void finishTask(BaseTaskReporter::Task task);
    void updateTask(BaseTaskReporter::Task task);
  signals:
    void channelChanged(std::string newChannel);

  private:
    void setupUI();
    QWidget &imageWidget;
    PanAndZoomArea *panAndZoomArea;
    SmallIconToggleButton *metadataButton;
    QTreeWidget *imageMetadataWidget;
    QComboBox *channelComboBox;
    QProgressBar *statusProgressBar;
    QLabel *statusElapsed;
    QLabel *statusRemaining;
    QLabel *statusEstimatedTotal;
    QLabel *statusPreviousTask;
    IconToggleButton *followMouseToggle;
};

}
