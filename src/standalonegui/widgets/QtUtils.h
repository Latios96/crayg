#ifndef CRAYG_SRC_STANDALONEGUI_WIDGETS_QTUTILS_H_
#define CRAYG_SRC_STANDALONEGUI_WIDGETS_QTUTILS_H_

#include <QApplication>
#include <QString>
#include <fmt/format.h>

namespace crayg {

template <typename... T> QString qformat(fmt::format_string<T...> fmt, T &&...args) {
    return QString::fromStdString(fmt::vformat(fmt, fmt::make_format_args(args...)));
}

void applyStyleSheet(QApplication &application);

}

#endif // CRAYG_SRC_STANDALONEGUI_WIDGETS_QTUTILS_H_
