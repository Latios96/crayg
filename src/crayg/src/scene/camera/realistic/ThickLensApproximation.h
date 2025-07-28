#pragma once

#include "basics/Ray.h"
#include "utils/DtoUtils.h"

namespace crayg {

struct CameraLens;

CRAYG_DTO_2(CardinalPoints, float, pZ, float, fZ);
CRAYG_DTO_2(ThickLensApproximation, CardinalPoints, firstCardinalPoints, CardinalPoints, secondCardinalPoints);

float calculateEffectiveFocalLength(const ThickLensApproximation &thickLensApproximation);

class ThickLensApproximationCalculator {
  public:
    explicit ThickLensApproximationCalculator(const CameraLens &lens);

    enum class Direction { HORIZONTAL, VERTICAL };

    ThickLensApproximation calculate(const Direction &direction);

  private:
    CardinalPoints computeHorizontalCardinalPoints(const Ray &in, const Ray &out);
    CardinalPoints computeVerticalCardinalPoints(const Ray &in, const Ray &out);
    const CameraLens &lens;
};

}
