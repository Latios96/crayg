#pragma once
#include <ImfPixelType.h>
#include <fmt/ostream.h>
#include <magic_enum.hpp>

namespace std {

std::ostream &operator<<(std::ostream &os, Imf::PixelType value);

}

template <> struct fmt::formatter<Imf::PixelType> : ostream_formatter {};
