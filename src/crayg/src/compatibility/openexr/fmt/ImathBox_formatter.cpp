#include "ImathBox_formatter.h"

namespace std {

std::ostream &operator<<(std::ostream &os, const Imath::Box2i &box) {
    os << fmt::format("[({},{}),({},{})]", box.min.x, box.min.y, box.max.x, box.max.y);
    return os;
}

}