#pragma once
#include <ImathBox.h>
#include <fmt/ostream.h>

namespace std {

std::ostream &operator<<(std::ostream &os, const Imath::Box2i &box);

}

template <> struct fmt::formatter<Imath::Box2i> : ostream_formatter {};
