#pragma once
#include "basics/Resolution.h"
#include <QtWidgets/qwidget.h>

namespace crayg {

class NextGenImageWidget : public QWidget {
    Q_OBJECT

  public:
    explicit NextGenImageWidget(QWidget *parent = nullptr);
    void initBuffer(const Resolution &resolution);

  protected:
    void paintEvent(QPaintEvent *event) override;

  public:
    QImage displayBuffer;
};

}