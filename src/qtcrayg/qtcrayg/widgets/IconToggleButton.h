#pragma once
#include <QCheckBox>

namespace crayg {

class IconToggleButton : public QCheckBox {
    Q_OBJECT
  public:
    explicit IconToggleButton(QWidget *parent = nullptr);
};

class SmallIconToggleButton : public IconToggleButton {
    Q_OBJECT
  public:
    explicit SmallIconToggleButton(QWidget *parent = nullptr);
};

}
