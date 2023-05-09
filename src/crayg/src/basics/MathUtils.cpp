#include "MathUtils.h"
#include <cmath>

namespace crayg {

std::optional<QuadraticSolutions> MathUtils::solveQuadratic(float a, float b, float c) {
    const bool isNoEquation = a == 0 && b == 0;
    if (isNoEquation) {
        return std::nullopt;
    }

    const bool isLinear = a == 0;
    if (isLinear) {
        return QuadraticSolutions{-c / b, -c / b};
    }

    const float discriminant = b * b - 4 * a * c;
    const bool hasNoRealSolution = discriminant < 0;
    if (hasNoRealSolution) {
        return std::nullopt;
    }

    const float rootOfDiscriminant = std::sqrt(discriminant);
    float t0 = (-b + rootOfDiscriminant) / (2 * a);
    float t1 = (-b - rootOfDiscriminant) / (2 * a);
    if (t0 > t1) {
        std::swap(t0, t1);
    }
    return QuadraticSolutions{t0, t1};
}

}