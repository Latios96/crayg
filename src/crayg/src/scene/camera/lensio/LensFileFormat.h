#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEFORMAT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEFORMAT_H_

#include <fmt/core.h>
#include <magic_enum.hpp>

namespace crayg {

enum class LensFileFormat { TXT, JSON };

}

template <> struct fmt::formatter<crayg::LensFileFormat> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(crayg::LensFileFormat const &lensFileFormat, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), magic_enum::enum_name(lensFileFormat));
    };
};

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEFORMAT_H_
