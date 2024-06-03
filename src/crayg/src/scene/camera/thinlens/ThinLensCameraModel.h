#pragma once

#include "scene/camera/pinehole/PineHoleCameraModel.h"

namespace crayg {

class ThinLensCameraModel : public PineHoleCameraModel {
  public:
    ThinLensCameraModel(Camera &camera, const Resolution &resolution);

    RayWithWeight createPrimaryRay(const Vector2f &pixelPos, float wavelength) override;
};

} // crayg
