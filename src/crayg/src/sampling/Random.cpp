#include <cstdlib>
#include "Random.h"

namespace crayg {
float Random::random() {
    return ((float) rand() / (RAND_MAX));
}
} // crayg