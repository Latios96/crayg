#pragma once

#include "Bound2d.h"
#include "Vector2_formatter.h"
#include "crayg/foundation/objects/ToStringHelper.h"

namespace crayg {

std::ostream &operator<<(std::ostream &os, const Bounds2df &d) {
    os << ToStringHelper("Bounds2d").addMember("min", d.min).addMember("max", d.max).finish();
    return os;
}

std::ostream &operator<<(std::ostream &os, const Bounds2di &d) {
    os << ToStringHelper("Bounds2d").addMember("min", d.min).addMember("max", d.max).finish();
    return os;
}

}
