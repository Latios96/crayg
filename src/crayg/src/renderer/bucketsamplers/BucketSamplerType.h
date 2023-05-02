#ifndef CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_BUCKETSAMPLERTYPE_H_
#define CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_BUCKETSAMPLERTYPE_H_
#include <fmt/format.h>
#include <magic_enum.hpp>

namespace crayg {

enum class BucketSamplerType { UNIFORM = 1, ADAPTIVE = 2 };

}

template <> struct fmt::formatter<crayg::BucketSamplerType> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(crayg::BucketSamplerType const &integratorType, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), magic_enum::enum_name(integratorType));
    };
};

#endif // CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_BUCKETSAMPLERTYPE_H_
