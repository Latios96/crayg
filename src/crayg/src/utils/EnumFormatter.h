#pragma once
#include <fmt/format.h>
#include <magic_enum.hpp>

#define CRAYG_FMT_ENUM_FORMATTER(FullQualifiedType)                                                                    \
    template <> struct fmt::formatter<FullQualifiedType> {                                                             \
        template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }               \
                                                                                                                       \
        template <typename FormatContext> auto format(FullQualifiedType const &integratorType, FormatContext &ctx) {   \
            return fmt::format_to(ctx.out(), magic_enum::enum_name(integratorType));                                   \
        };                                                                                                             \
    }