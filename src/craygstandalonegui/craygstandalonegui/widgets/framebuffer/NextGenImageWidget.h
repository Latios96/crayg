#pragma once

// clang-format off
#include <QtWidgets/qwidget.h>
// clang-format on

#include "basics/Resolution.h"

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