#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERATYPE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERATYPE_H_

#include <fmt/format.h>
#include <magic_enum.hpp>

namespace crayg {

enum class CameraType { PINE_HOLE = 1, THIN_LENS = 2, REALISTIC = 3 };

}

template <> struct fmt::formatter<crayg::CameraType> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(crayg::CameraType const &cameraType, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), magic_enum::enum_name(cameraType));
    };
};

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERATYPE_H_
