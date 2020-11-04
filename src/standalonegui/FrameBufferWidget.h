//
// Created by Jan on 04.11.2020.
//

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

class FrameBufferWidget : public QWidget {
 Q_OBJECT
 public:
    explicit FrameBufferWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
    }
    ~FrameBufferWidget() override = default;
 private:
    void setupUI();
    QImage image;
};

#endif //CRAYG_SRC_STANDALONE_GUI_FRAMEBUFFERWIDGET_H_
