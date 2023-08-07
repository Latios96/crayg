#include "IconToggleButton.h"
#include "Logger.h"
#include <QVariant>

namespace crayg {
IconToggleButton::IconToggleButton(QWidget *parent) : QCheckBox(parent) {
}

SmallIconToggleButton::SmallIconToggleButton(QWidget *parent) : IconToggleButton(parent) {
    const int size = 25;
    this->setMinimumHeight(size);
    this->setMaximumHeight(size);
    this->setMinimumWidth(size);
    this->setMaximumWidth(size);
}
} // crayg