#pragma once
#include <ImathBox.h>
#include <fmt/format.h>

namespace std {

inline std::ostream &operator<<(std::ostream &os, const Imath::Box2i &box) {
    os << fmt::format("[({},{}),({},{})]", box.min.x, box.min.y, box.max.x, box.max.y);
    return os;
}

}

template <> struct fmt::formatter<Imath::Box2i> : ostream_formatter {};
