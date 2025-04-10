#pragma once

#include "Camera.h"
#include "basics/Resolution.h"
#include "utils/DtoUtils.h"
#include "utils/TaskReporter.h"
#include <basics/Ray.h>
#include <basics/Vector2.h>
#include <fmt/std.h>
#include <optional>

namespace crayg {

CRAYG_DTO_2(RayWithWeight, std::optional<Ray>, ray, float, weight);

class CameraModel {
  public:
    CameraModel(Camera &camera, const Resolution &resolution) : camera(camera), resolution(resolution) {
    }

    virtual void init(crayg::BaseTaskReporter &taskReporter){};

    virtual RayWithWeight createPrimaryRay(const Vector2f &pixelPos, float wavelength) = 0;

    virtual ~CameraModel() = default;

  protected:
    Camera &camera;
    Resolution resolution;
};

}
