#pragma once
#include "utils/DtoUtils.h"
#include <optional>

namespace crayg {

CRAYG_DTO_2(QuadraticSolutions, float, t0, float, t1);

class QuadraticEquations {
  public:
    template <typename T, typename V> static V lerp(T t, V val1, V val2) {
        return val1 * (1 - t) + val2 * t;
    }

    static std::optional<QuadraticSolutions> solveQuadratic(float a, float b, float c) {
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
};

}
