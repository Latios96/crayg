#include "Color.h"
#include "crayg/foundation/objects/ToStringHelper.h"
#include "crayg/renderer/sampling/Random.h"
#include <algorithm>
#include <tuple>

namespace crayg {

CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(Color, r, g, b);

Color Color::createRandom() {
    return {Random::random(), Random::random(), Random::random()};
}

}