#pragma once
#include <ImfCompression.h>
#include <fmt/ostream.h>

namespace std {

std::ostream &operator<<(std::ostream &os, Imf::Compression value);

}

template <> struct fmt::formatter<Imf::Compression> : ostream_formatter {};
