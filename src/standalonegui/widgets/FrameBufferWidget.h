#ifndef CRAYG_SRC_STANDALONE_GUI_FRAMEBUFFERWIDGET_H_
#define CRAYG_SRC_STANDALONE_GUI_FRAMEBUFFERWIDGET_H_

#include <fmt/format.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qscrollarea.h>
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QScreen>
#include <iostream>
#include <QTreeWidget>
#include "ImageWidget.h"
#include "PanAndZoomArea.h"
#include "image/ImageMetadata.h"

namespace crayg {

class FrameBufferWidget : public QWidget {
 Q_OBJECT
 public:
    FrameBufferWidget(ImageWidget &imageWidget, QWidget *parent = nullptr)
        : QWidget(parent), imageWidget(imageWidget) {
        setupUI();
    }
    ~FrameBufferWidget() override = default;
 public slots:
    void setZoomFactor(ZoomFactor zoomFactor);
    void setImageMetadata(ImageMetadata imageMetadata);
    void setImageSpec(ImageSpec imageSpec);
 signals:
    void channelChanged(std::string newChannel);
 private:
    void setupUI();
    ImageWidget &imageWidget;
    PanAndZoomArea *panAndZoomArea;
    QPushButton *metadataButton;
    QTreeWidget *imageMetadataWidget;
    QComboBox *channelComboBox;
};

}

#endif //CRAYG_SRC_STANDALONE_GUI_FRAMEBUFFERWIDGET_H_
