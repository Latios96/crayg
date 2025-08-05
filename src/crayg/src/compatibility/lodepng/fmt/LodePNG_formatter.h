#pragma once
#include "utils/EnumFormatter.h"
#include <fmt/format.h>
#include <lodepng.h>
#include <magic_enum.hpp>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const LodePNGColorType &value) {
    os << magic_enum::enum_name(value);
    return os;
}

CRAYG_FMT_ENUM_FORMATTER(LodePNGColorType);
