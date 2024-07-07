#pragma once

#include <QPoint>
#include <QSize>
#include <QString>
#include <fmt/format.h>

template <> struct fmt::formatter<QString> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(QString const &qString, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}", qString.toStdString());
    };
};

template <> struct fmt::formatter<QPoint> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(QPoint const &qPoint, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "({},{}))", qPoint.x(), qPoint.y());
    };
};

template <> struct fmt::formatter<QPointF> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(QPointF const &qPoint, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "({},{}))", qPoint.x(), qPoint.y());
    };
};

template <> struct fmt::formatter<QSize> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(QSize const &size, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}x{}", size.width(), size.height());
    };
};

template <> struct fmt::formatter<QSizeF> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(QSizeF const &size, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "({},{}))", size.width(), size.height());
    };
};
