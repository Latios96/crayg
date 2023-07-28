#ifndef CRAYG_CAMERAMODEL_H
#define CRAYG_CAMERAMODEL_H

#include "Camera.h"
#include "basics/Resolution.h"
#include "utils/DtoUtils.h"
#include "utils/TaskReporter.h"
#include <basics/Ray.h>
#include <optional>

namespace crayg {

CRAYG_DTO_2(RayWithWeight, std::optional<Ray>, ray, float, weight);

class CameraModel {
  public:
    CameraModel(Camera &camera, const Resolution &resolution) : camera(camera), resolution(resolution) {
    }

    virtual void init(crayg::TaskReporter &taskReporter){};

    virtual RayWithWeight createPrimaryRay(float x, float y) = 0;

    virtual ~CameraModel() = default;

  protected:
    Camera &camera;
    Resolution resolution;
};

}
#endif // CRAYG_CAMERAMODEL_H
