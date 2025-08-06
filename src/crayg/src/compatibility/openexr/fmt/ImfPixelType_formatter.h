#pragma once
#include <ImfPixelType.h>
#include <fmt/ostream.h>

namespace std {

inline std::ostream &operator<<(std::ostream &os, Imf::PixelType value) {
    os << magic_enum::enum_name(value);
    return os;
}

}

template <> struct fmt::formatter<Imf::PixelType> : ostream_formatter {};
