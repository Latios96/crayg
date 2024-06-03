#pragma once

#include <QApplication>
#include <QString>
#include <fmt/format.h>

namespace crayg {

template <typename... T> QString qformat(fmt::format_string<T...> fmt, T &&...args) {
    return QString::fromStdString(fmt::vformat(fmt, fmt::make_format_args(args...)));
}

void applyStyleSheet(QApplication &application);

}
