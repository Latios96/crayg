#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUPCAMERAMODEL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUPCAMERAMODEL_H_

#include "CameraModel.h"
#include "RealisticCameraModel.h"
#include "scene/camera/lookup/LensRayLookupTable.h"

namespace crayg {

class LookupCameraModel : public RealisticCameraModel {
  public:
    void init() override;
    std::optional<Ray> createPrimaryRay(float x, float y) override;
    LensRayLookupTable lensRayLookupTable;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUPCAMERAMODEL_H_
