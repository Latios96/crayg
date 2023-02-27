#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORTYPE_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORTYPE_H_

#include <fmt/format.h>
#include <magic_enum.hpp>

namespace crayg {

enum class IntegratorType { RAYTRACING = 1, DEBUG = 2, AMBIENT_OCCLUSION = 3 };

}

template <> struct fmt::formatter<crayg::IntegratorType> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(crayg::IntegratorType const &integratorType, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), magic_enum::enum_name(integratorType));
    };
};

#endif // CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORTYPE_H_
