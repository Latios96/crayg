#pragma once

#include <fmt/format.h>
#include <pxr/base/tf/token.h>

template <> struct fmt::formatter<pxr::TfToken> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(pxr::TfToken const &tfToken, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}", tfToken.GetString());
    };
};
