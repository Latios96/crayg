#ifndef CRAYG_UTILS_H
#define CRAYG_UTILS_H

#include <cmath>
#include <string>

namespace crayg {

inline bool compareWithPrecision(float A, float B, float epsilon = 0.001f) {
    return (fabs(A - B) < epsilon);
}

std::string stripCommentFromLine(std::string line);

}
#endif // CRAYG_UTILS_H