#pragma once

#include "crayg/scene/camera/pinhole/PinholeCameraModel.h"

namespace crayg {

class ThinLensCameraModel : public PinholeCameraModel {
  public:
    ThinLensCameraModel(Camera &camera, const Resolution &resolution);

    RayWithWeight createPrimaryRay(const Vector2f &pixelPos, float wavelength) override;
};

}
