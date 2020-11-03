//
// Created by Jan Honsbrok on 11.10.19.
//

#include <stdlib.h>
#include "UnitSphereSampler.h"
Vector3f UnitSphereSampler::randomPointInside() {
    const Vector3f one = Vector3f(1, 1, 1);
    Vector3f point;
    do {
        point = (Vector3f((double(rand()) / RAND_MAX), (double(rand()) / RAND_MAX), (double(rand()) / RAND_MAX)) * 2.0)
            - one;
    } while (point.length() >= 1.0);
    return point;
}
