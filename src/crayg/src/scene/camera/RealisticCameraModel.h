#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTICCAMERA_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTICCAMERA_H_

#include "CameraLens.h"
#include "CameraModel.h"
#include "ExitPupilCalculator.h"
#include "ThickLensApproximation.h"
#include <basics/Ray.h>

namespace crayg {

class RealisticCameraModel : public CameraModel {
  public:
    RealisticCameraModel(Camera &camera, const Resolution &resolution);
    void init() override;
    std::optional<Ray> createPrimaryRay(float x, float y) override;

  private:
    ExitPupil exitPupil;
    Bounds2df filmPhysicalExtend;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTICCAMERA_H_
