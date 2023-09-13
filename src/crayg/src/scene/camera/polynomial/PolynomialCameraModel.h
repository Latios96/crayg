#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMIAL_POLYNOMIALCAMERAMODEL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMIAL_POLYNOMIALCAMERAMODEL_H_

#include "basics/Bound2d.h"
#include "scene/camera/CameraModel.h"

namespace crayg {

class PolynomialCameraModel : public CameraModel {
  public:
    PolynomialCameraModel(Camera &camera, const Resolution &resolution);
    void init(BaseTaskReporter &taskReporter) override;
    RayWithWeight createPrimaryRay(float x, float y, float wavelength) override;
    ~PolynomialCameraModel() override = default;

  private:
    Bounds2df filmPhysicalExtend;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMIAL_POLYNOMIALCAMERAMODEL_H_
