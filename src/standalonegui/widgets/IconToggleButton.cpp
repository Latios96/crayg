#include "IconToggleButton.h"
#include "Logger.h"

namespace crayg {
IconToggleButton::IconToggleButton(QWidget *parent) : QCheckBox(parent) {
    this->setMinimumWidth(30);
    this->setMinimumHeight(30);
}
} // crayg