#include "ThickLensApproximation.h"
#include "CameraLens.h"

namespace crayg {

float calculateEffectiveFocalLength(const ThickLensApproximation &thickLensApproximation) {
    return thickLensApproximation.firstCardinalPoints.fZ - thickLensApproximation.firstCardinalPoints.pZ;
}

ThickLensApproximationCalculator::ThickLensApproximationCalculator(const CameraLens &lens) : lens(lens) {
}

ThickLensApproximation ThickLensApproximationCalculator::calculate(const Direction &direction) {
    const int factor = 100;
    const float offsetX = direction == HORIZONTAL ? 3.5e-05f * factor : 0;
    const float offsetY = direction == VERTICAL ? 3.5e-05f * factor : 0;

    const Ray fromWorldToFilmIn{{offsetX, offsetY, lens.getFirstElement().center + 1 * factor}, {0, 0, -1}};
    auto fromWorldToFilmOut = lens.traceFromWorldToFilm(fromWorldToFilmIn);
    if (!fromWorldToFilmOut) {
        throw std::runtime_error(
            "Could not trace ray from world to film to compute thick lens approximation. Is aperture stop very small?");
    }
    const auto firstCardinalPoints = direction == HORIZONTAL
                                         ? computeHorizontalCardinalPoints(fromWorldToFilmIn, *fromWorldToFilmOut)
                                         : computeVerticalCardinalPoints(fromWorldToFilmIn, *fromWorldToFilmOut);

    Ray fromFilmToWorldIn{{offsetX, offsetY, lens.getLastElement().center - 1 * factor}, {0, 0, 1}};
    auto fromFilmToWorldOut = lens.traceFromFilmToWorld(fromFilmToWorldIn);
    if (!fromFilmToWorldOut) {
        throw std::runtime_error(
            "Could not trace ray from film to world to compute thick lens approximation. Is aperture stop very small?");
    }
    const auto secondCardinalPoints = direction == HORIZONTAL
                                          ? computeHorizontalCardinalPoints(fromFilmToWorldIn, *fromFilmToWorldOut)
                                          : computeVerticalCardinalPoints(fromFilmToWorldIn, *fromFilmToWorldOut);

    return {firstCardinalPoints, secondCardinalPoints};
}

CardinalPoints ThickLensApproximationCalculator::computeHorizontalCardinalPoints(const Ray &in, const Ray &out) {
    const float ft = -out.startPoint.x / out.direction.x;
    const float fz = -(out.startPoint.z + out.direction.z * ft);
    float pt = (in.startPoint.x - out.startPoint.x) / out.direction.x;
    const float pz = -(out.startPoint.z + out.direction.z * pt);
    return {pz, fz};
}

CardinalPoints ThickLensApproximationCalculator::computeVerticalCardinalPoints(const Ray &in, const Ray &out) {
    const float ft = -out.startPoint.y / out.direction.y;
    const float fz = -(out.startPoint.z + out.direction.z * ft);
    float pt = (in.startPoint.y - out.startPoint.y) / out.direction.y;
    const float pz = -(out.startPoint.z + out.direction.z * pt);
    return {pz, fz};
}

} // crayg