#pragma once

#include <fmt/format.h>
#include <pxr/usd/sdf/path.h>

#include <fmt/format.h>
#include <pxr/base/tf/token.h>
#include <pxr/usd/sdf/valueTypeName.h>
#include <pxr/usd/usd/stage.h>

template <> struct fmt::formatter<pxr::SdfPath> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(pxr::SdfPath const &sdfPath, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}", sdfPath.GetString());
    };
};
