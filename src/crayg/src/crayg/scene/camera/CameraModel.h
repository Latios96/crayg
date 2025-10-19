#pragma once

#include "Camera.h"
#include "crayg/foundation/math/geometry/Ray.h"
#include "crayg/foundation/math/geometry/Ray_formatter.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/math/geometry/Vector2.h"
#include "crayg/foundation/objects/DtoUtils.h"
#include "crayg/foundation/progress/TaskReporter.h"
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
