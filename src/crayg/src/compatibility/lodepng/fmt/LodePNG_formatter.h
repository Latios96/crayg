#pragma once
#include "utils/EnumFormatter.h"
#include <fmt/format.h>
#include <lodepng.h>
#include <magic_enum.hpp>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const LodePNGColorType &value);

template <> struct fmt::formatter<LodePNGColorType> : ostream_formatter {};
