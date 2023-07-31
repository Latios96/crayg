#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THINLENSCAMERAMODEL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THINLENSCAMERAMODEL_H_

#include "scene/camera/pinehole/PineHoleCameraModel.h"

namespace crayg {

class ThinLensCameraModel : public PineHoleCameraModel {
  public:
    ThinLensCameraModel(Camera &camera, const Resolution &resolution);

    RayWithWeight createPrimaryRay(float x, float y, float wavelength) override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_THINLENSCAMERAMODEL_H_
