#ifndef CRAYG_SRC_STANDALONEGUI_WIDGETS_ICONTOGGLEBUTTON_H_
#define CRAYG_SRC_STANDALONEGUI_WIDGETS_ICONTOGGLEBUTTON_H_
#include <QCheckBox>

namespace crayg {

class IconToggleButton : public QCheckBox {
    Q_OBJECT
  public:
    explicit IconToggleButton(QWidget *parent = nullptr);
};

} // crayg

#endif // CRAYG_SRC_STANDALONEGUI_WIDGETS_ICONTOGGLEBUTTON_H_
