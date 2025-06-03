#pragma once
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <magic_enum.hpp>

#define CRAYG_FMT_ENUM_FORMATTER(FullQualifiedType)                                                                    \
    namespace crayg {                                                                                                  \
                                                                                                                       \
    inline std::ostream &operator<<(std::ostream &os, const FullQualifiedType &v) {                                    \
        os << magic_enum::enum_name(v);                                                                                \
        return os;                                                                                                     \
    }                                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    template <> struct fmt::formatter<FullQualifiedType> : ostream_formatter {};
