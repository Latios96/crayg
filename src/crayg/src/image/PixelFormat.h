#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELFORMAT_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELFORMAT_H_

#include <fmt/core.h>
#include <magic_enum.hpp>

namespace crayg {

enum class PixelFormat {
    FLOAT,
    UINT8
};

}

template<>
struct fmt::formatter<crayg::PixelFormat> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(crayg::PixelFormat const &integratorType, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), magic_enum::enum_name(integratorType));
    };
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELFORMAT_H_
