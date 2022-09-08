#ifndef CRAYG_SRC_STANDALONE_GUI_FRAMEBUFFERWIDGET_H_
#define CRAYG_SRC_STANDALONE_GUI_FRAMEBUFFERWIDGET_H_

#include <fmt/format.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qscrollarea.h>
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QScreen>
#include <iostream>
#include "ImageWidget.h"
#include "PanAndZoomArea.h"

namespace crayg {

class FrameBufferWidget : public QWidget {
 Q_OBJECT
 public:
    explicit FrameBufferWidget(ImageWidget &imageWidget, QWidget *parent = nullptr)
        : QWidget(parent), imageWidget(imageWidget) {
        setupUI();
    }
    ~FrameBufferWidget() override = default;
 public slots:
    void setZoomFactor(ZoomFactor zoomFactor);
 private:
    void setupUI();
    ImageWidget &imageWidget;
    PanAndZoomArea *panAndZoomArea;
};

}

#endif //CRAYG_SRC_STANDALONE_GUI_FRAMEBUFFERWIDGET_H_
