#pragma once

#include <fmt/format.h>
#include <pxr/usd/sdf/valueTypeName.h>

template <> struct fmt::formatter<pxr::SdfValueTypeName> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(pxr::SdfValueTypeName const &sdfValueTypeName, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}", sdfValueTypeName.GetAsToken().GetString());
    };
};