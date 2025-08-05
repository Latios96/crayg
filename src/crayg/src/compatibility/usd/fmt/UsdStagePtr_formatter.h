#pragma once

#include <fmt/format.h>
#include <pxr/usd/usd/stage.h>

template <> struct fmt::formatter<pxr::UsdStagePtr> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(pxr::UsdStagePtr const &stage, FormatContext &ctx) {
        std::string result;
        stage->ExportToString(&result);
        return fmt::format_to(ctx.out(), "{}", result);
    };
};
