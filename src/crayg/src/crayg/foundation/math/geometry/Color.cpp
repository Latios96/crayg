#include "Color.h"
#include "crayg/foundation/objects/ToStringHelper.h"
#include "crayg/renderer/sampling/Random.h"
#include <algorithm>
#include <tuple>

namespace crayg {

std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << ToStringHelper("Color").addMember("r", color.r).addMember("g", color.g).addMember("b", color.b).finish();
    return os;
}

Color Color::createRandom() {
    return {Random::random(), Random::random(), Random::random()};
}

}