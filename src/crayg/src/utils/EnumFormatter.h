#pragma once
#include <fmt/format.h>
#include <magic_enum.hpp>

#define CRAYG_FMT_ENUM_FORMATTER(FullQualifiedType)                                                                    \
    template <> struct fmt::formatter<FullQualifiedType> : formatter<string_view> {                                    \
                                                                                                                       \
        auto format(const FullQualifiedType &enumValue, format_context &ctx) const -> format_context::iterator {       \
            const std::string_view name = magic_enum::enum_name(enumValue);                                            \
            return formatter<string_view>::format(name, ctx);                                                          \
        }                                                                                                              \
    };
