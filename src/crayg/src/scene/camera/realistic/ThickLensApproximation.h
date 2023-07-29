#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THICKLENSAPPROXIMATION_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THICKLENSAPPROXIMATION_H_

#include "basics/Ray.h"
#include "utils/DtoUtils.h"

namespace crayg {

struct CameraLens;

CRAYG_DTO_2(CardinalPoints, float, pZ, float, fZ);
CRAYG_DTO_2(ThickLensApproximation, CardinalPoints, firstCardinalPoints, CardinalPoints, secondCardinalPoints);

float calculateEffectiveFocalLength(const ThickLensApproximation &thickLensApproximation);
float calculateEffectiveFocalLength(
    const CameraLens &cameraLens); // todo move to Utils or something else to match code style

class ThickLensApproximationCalculator {
  public:
    explicit ThickLensApproximationCalculator(const CameraLens &lens);
    ThickLensApproximation calculate();

  private:
    CardinalPoints computeCardinalPoints(const Ray &in, const Ray &out);
    const CameraLens &lens;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THICKLENSAPPROXIMATION_H_