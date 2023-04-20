#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUPCAMERAMODEL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUPCAMERAMODEL_H_

#include "CameraModel.h"
#include "RealisticCameraModel.h"

namespace crayg {

class LookupCameraModel : public RealisticCameraModel {
  public:
    std::optional<Ray> createPrimaryRay(float x, float y) override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUPCAMERAMODEL_H_
