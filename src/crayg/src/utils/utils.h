//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_UTILS_H
#define CRAYG_UTILS_H

#include <cmath>

inline bool compareWithPrecision(float A, float B, float epsilon = 0.001f) {
    return (fabs(A - B) < epsilon);
}
#endif //CRAYG_UTILS_H