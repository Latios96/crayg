#pragma once

#include "craygstandalonegui/widgets/panandzoomarea/PanAndZoomArea.h"
#include "image/ImageMetadata.h"
#include "image/ImageSpec.h"
#include "image/film/FilmSpec.h"
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
    void setZoomFactor(ZoomFactor zoomFactor); // todo remove, connect to generateWindowTitle
    void setImageMetadata(ImageMetadata imageMetadata);
    void setImageSpec(ImageSpec imageSpec);
    void setFilmSpec(FilmSpec filmSpec);
    void startTask(BaseTaskReporter::Task task);
    void finishTask(BaseTaskReporter::Task task);
    void updateTask(BaseTaskReporter::Task task);
    void generateWindowTitle();
  signals:
    void channelChanged(std::string newChannel);

  private:
    void setupUI();
    void adaptToAvailableSize();
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
    Resolution resolution;
};

}
