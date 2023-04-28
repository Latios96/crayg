#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORTYPE_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORTYPE_H_

#include <fmt/format.h>
#include <magic_enum.hpp>

namespace crayg {

enum class IntersectorType { EMBREE = 2 };

}

template <> struct fmt::formatter<crayg::IntersectorType> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(crayg::IntersectorType const &intersectorType, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), magic_enum::enum_name(intersectorType));
    };
};

#endif // CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORTYPE_H_
