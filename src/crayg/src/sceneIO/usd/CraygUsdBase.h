#ifndef CRAYG_SRC_CRAYGUSD_SRC_CRAYGUSDBASE_H_
#define CRAYG_SRC_CRAYGUSD_SRC_CRAYGUSDBASE_H_
#include <fmt/format.h>
#include <pxr/base/tf/token.h>
#include <pxr/usd/sdf/path.h>

template<>
struct fmt::formatter<pxr::TfToken> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(pxr::TfToken const &tfToken, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), tfToken.GetString());
    };
};

template<>
struct fmt::formatter<pxr::SdfPath> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(pxr::SdfPath const &sdfPath, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), sdfPath.GetString());
    };
};

#endif //CRAYG_SRC_CRAYGUSD_SRC_CRAYGUSDBASE_H_
