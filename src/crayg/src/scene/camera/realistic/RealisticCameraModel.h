#pragma once

#include "CameraLens.h"
#include "ExitPupilCalculator.h"
#include "ThickLensApproximation.h"
#include "scene/camera/CameraModel.h"
#include <basics/Ray.h>

namespace crayg {

class RealisticCameraModel : public CameraModel {
  public:
    RealisticCameraModel(Camera &camera, const Resolution &resolution);
    void init(BaseTaskReporter &taskReporter) override;
    RayWithWeight createPrimaryRay(const Vector2f &pixelPos, float wavelength) override;

  private:
    ExitPupil exitPupil;
    Bounds2df filmPhysicalExtend;
    float filmDiagonal;
};

} // crayg
