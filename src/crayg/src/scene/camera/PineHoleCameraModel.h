#ifndef CRAYG_PINEHOLECAMERAMODEL_H
#define CRAYG_PINEHOLECAMERAMODEL_H

#include "CameraModel.h"
#include "basics/Ray.h"
#include "basics/Resolution.h"
#include "scene/camera/Camera.h"

namespace crayg {

// todo add tests
class PineHoleCameraModel : public CameraModel {
  private:
    float imageRatio;
    float imagePlaneWidth, imagePlaneHeight;

    Vector3f sideVector, upVector, viewVector, planeCenter;

    Vector3f getPixelCenter(float x, float y);

  public:
    PineHoleCameraModel(Camera &camera, const Resolution &resolution);

    Ray createPrimaryRay(float x, float y) override;
};

}

#endif // CRAYG_PINEHOLECAMERAMODEL_H
