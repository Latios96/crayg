#pragma once

#include <fmt/format.h>
#include <pxr/usd/sdf/path.h>

template <> struct fmt::formatter<pxr::SdfPath> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(pxr::SdfPath const &sdfPath, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}", sdfPath.GetString());
    };
};
