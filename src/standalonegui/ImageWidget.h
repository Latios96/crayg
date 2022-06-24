#ifndef CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_
#define CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_

#include <QPainter>
#include <QtWidgets/qwidget.h>
#include <basics/Resolution.h>

namespace crayg {

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

}

#endif //CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_
