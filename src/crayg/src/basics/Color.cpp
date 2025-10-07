#include "Color.h"
#include "sampling/Random.h"
#include <algorithm>
#include <tuple>
#include <utils/ToStringHelper.h>

namespace crayg {

std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << ToStringHelper("Color").addMember("r", color.r).addMember("g", color.g).addMember("b", color.b).finish();
    return os;
}

Color Color::createRandom() {
    return {Random::random(), Random::random(), Random::random()};
}

}