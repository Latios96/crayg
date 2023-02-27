#include "Random.h"
#include <cstdlib>

namespace crayg {
float Random::random() {
    return ((float)rand() / (RAND_MAX));
}
} // crayg