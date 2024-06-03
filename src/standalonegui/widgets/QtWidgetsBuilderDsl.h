#pragma once

#include <QLayout>
#include <QWidget>
#include <variant>

namespace crayg {

typedef std::variant<QLayout *, QWidget *, std::function<QWidget *()>, QSpacerItem *> Renderable;

QSpacerItem *addHStretch();

QSpacerItem *addVStretch();

QSpacerItem *addHSpacer(int width);

QSpacerItem *addVSpacer(int height);

QLayout *inHBox(const std::vector<Renderable> &children);

QLayout *inVBox(const std::vector<Renderable> &children);

} // crayg
