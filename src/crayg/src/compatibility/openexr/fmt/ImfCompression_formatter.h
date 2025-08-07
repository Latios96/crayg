#pragma once
#include <ImfCompression.h>
#include <fmt/ostream.h>
#include <magic_enum.hpp>

namespace std {

inline std::ostream &operator<<(std::ostream &os, Imf::Compression value) {
    os << magic_enum::enum_name(value);
    return os;
}

}

template <> struct fmt::formatter<Imf::Compression> : ostream_formatter {};
