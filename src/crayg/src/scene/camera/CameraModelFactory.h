#pragma once
#include "Camera.h"
#include "CameraModel.h"
#include "basics/Resolution.h"
#include <memory>

namespace crayg {

class CameraModelFactory {
  public:
    static std::unique_ptr<CameraModel> createCameraModel(Camera &camera, const Resolution &resolution);
};
}
