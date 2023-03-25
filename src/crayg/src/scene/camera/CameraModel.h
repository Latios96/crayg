#ifndef CRAYG_CAMERAMODEL_H
#define CRAYG_CAMERAMODEL_H

#include "Camera.h"
#include "basics/Resolution.h"
#include <basics/Ray.h>

namespace crayg {

class CameraModel {
  public:
    CameraModel(Camera &camera, const Resolution &resolution) : camera(camera), resolution(resolution) {
    }

    virtual Ray createPrimaryRay(float x, float y) = 0;

    virtual ~CameraModel() = default;

  protected:
    Camera &camera;
    Resolution resolution;
};

}
#endif // CRAYG_CAMERAMODEL_H
