#include "UnitSphereSampler.h"
#include "Random.h"
#include <stdlib.h>

namespace crayg {

Vector3f UnitSphereSampler::randomPointInside() {
    const Vector3f one = Vector3f(1, 1, 1);
    Vector3f point;
    do {
        point = (Vector3f(Random::random(), Random::random(), Random::random()) * 2.0) - one;
    } while (point.length() >= 1.0);
    return point;
}

}
