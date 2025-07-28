#include "QtWidgetsBuilderDsl.h"

namespace crayg {

QSpacerItem *addHStretch() {
    return new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

QSpacerItem *addVStretch() {
    return new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
}

QSpacerItem *addHSpacer(int width) {
    return new QSpacerItem(width, 0);
}

QSpacerItem *addVSpacer(int height) {
    return new QSpacerItem(0, height);
}

template <typename T> void populateLayout(T *layout, const std::vector<Renderable> &children) {
    for (auto renderable : children) {
        if (std::holds_alternative<QLayout *>(renderable)) {
            layout->addLayout(std::get<QLayout *>(renderable));
        } else if (std::holds_alternative<QWidget *>(renderable)) {
            auto widget = std::get<QWidget *>(renderable);
            if (widget == nullptr) {
                layout->addStretch();
            } else {
                layout->addWidget(widget);
            }

        } else if (std::holds_alternative<std::function<QWidget *()>>(renderable)) {
            layout->addWidget(std::get<std::function<QWidget *()>>(renderable)());
        } else if (std::holds_alternative<QSpacerItem *>(renderable)) {
            layout->addSpacerItem(std::get<QSpacerItem *>(renderable));
        }
    }
}

QLayout *inHBox(const std::vector<Renderable> &children) {
    auto hBox = new QHBoxLayout();

    populateLayout(hBox, children);

    return hBox;
}

QLayout *inVBox(const std::vector<Renderable> &children) {
    auto vBox = new QVBoxLayout();

    populateLayout(vBox, children);

    return vBox;
}
}