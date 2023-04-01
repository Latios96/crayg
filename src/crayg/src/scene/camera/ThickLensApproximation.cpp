#include "ThickLensApproximation.h"

namespace crayg {

ThickLensApproximationCalculator::ThickLensApproximationCalculator(CameraLens &lens) : lens(lens) {
}

ThickLensApproximation ThickLensApproximationCalculator::calculate() {
    const float offsetX = 0.01 * 0.24f;

    Ray fromWorldToFilmIn{{offsetX, 0, lens.getFirstElement().center + 1}, {0, 0, -1}};
    auto fromWorldToFilmOut = lens.traceFromWorldToFilm(fromWorldToFilmIn);
    const auto firstCardinalPoints = computeCardinalPoints(fromWorldToFilmIn, fromWorldToFilmOut);

    Ray fromFilmToWorldIn{{offsetX, 0, lens.getLastElement().center - 1}, {0, 0, 1}};
    auto fromFilmToWorldOut = lens.traceFromFilmToWorld(fromWorldToFilmIn);
    const auto secondCardinalPoints = computeCardinalPoints(fromFilmToWorldIn, fromFilmToWorldOut);

    return {firstCardinalPoints, secondCardinalPoints};
}

CardinalPoints ThickLensApproximationCalculator::computeCardinalPoints(const Ray &in, const Ray &out) {
    const float ft = -out.startPoint.x / out.direction.x;
    const float fz = -out.startPoint.z + out.direction.z * ft;
    float pt = (in.startPoint.x - out.startPoint.x) / out.direction.x;
    const float pz = -out.startPoint.z + out.direction.z * pt;
    return {pz, fz};
}

} // crayg