#ifndef CRAYG_SRC_STANDALONEGUI_QTBASE_H_
#define CRAYG_SRC_STANDALONEGUI_QTBASE_H_

#include <fmt/format.h>
#include <QPoint>
#include <QSize>

template<>
struct fmt::formatter<QPoint> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(QPoint const &qPoint, FormatContext &ctx) {
        return fmt::format_to("({},{}))", qPoint.x(), qPoint.y());
    };
};

template<>
struct fmt::formatter<QPointF> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(QPointF const &qPoint, FormatContext &ctx) {
        return fmt::format_to("({},{}))", qPoint.x(), qPoint.y());
    };
};

template<>
struct fmt::formatter<QSize> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(QSize const &size, FormatContext &ctx) {
        return fmt::format_to("({},{}))", size.width(), size.height());
    };
};

template<>
struct fmt::formatter<QSizeF> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(QSizeF const &size, FormatContext &ctx) {
        return fmt::format_to("({},{}))", size.width(), size.height());
    };
};

#endif //CRAYG_SRC_STANDALONEGUI_QTBASE_H_
