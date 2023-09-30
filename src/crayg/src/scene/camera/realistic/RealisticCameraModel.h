#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTICCAMERA_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTICCAMERA_H_

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

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTICCAMERA_H_
