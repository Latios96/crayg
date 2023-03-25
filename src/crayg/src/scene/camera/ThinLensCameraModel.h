#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THINLENSCAMERAMODEL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THINLENSCAMERAMODEL_H_

#include "PineHoleCameraModel.h"

namespace crayg {

class ThinLensCameraModel : public PineHoleCameraModel {
  public:
    ThinLensCameraModel(Camera &camera, const Resolution &resolution);

    Ray createPrimaryRay(float x, float y) override;
    Vector3f calculateRayDirection(float x, float y);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THINLENSCAMERAMODEL_H_
