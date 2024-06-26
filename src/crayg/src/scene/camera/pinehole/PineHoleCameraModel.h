#pragma once

#include "basics/Ray.h"
#include "basics/Resolution.h"
#include "scene/camera/Camera.h"
#include "scene/camera/CameraModel.h"

namespace crayg {

class PineHoleCameraModel : public CameraModel {
  private:
    float imageRatio;
    float imagePlaneWidth, imagePlaneHeight;

    Vector3f sideVector = {1, 0, 0};
    Vector3f upVector = {0, 1, 0};
    Vector3f viewVector = {0, 0, 1};

  protected:
    Vector3f createPineHoleRayDirection(const Vector2f &pixelPos);

  public:
    PineHoleCameraModel(Camera &camera, const Resolution &resolution);

    RayWithWeight createPrimaryRay(const Vector2f &pixelPos, float wavelength) override;
};

}
