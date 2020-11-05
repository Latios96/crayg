//
// Created by Jan on 04.11.2020.
//

#ifndef CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_
#define CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_

#include <QPainter>
#include <QtWidgets/qwidget.h>
#include <basics/Resolution.h>
class ImageWidget : public QWidget {
 Q_OBJECT
    friend class ImageWidgetOutputDriver;
 public:
    explicit ImageWidget(const Resolution &resolution, QWidget *parent = nullptr);
 protected:
    void paintEvent(QPaintEvent *event) override;
 private:
    QImage image;
};

#endif //CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_
