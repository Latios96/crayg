#pragma once

#include <cmath>
#include <string>

namespace crayg {

inline bool compareWithPrecision(float A, float B, float epsilon = 0.001f) {
    return (fabs(A - B) < epsilon);
}

std::string stripCommentFromLine(std::string line);

}
