#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMALOPTICSCAMERAMODEL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMALOPTICSCAMERAMODEL_H_

#include "RealisticCameraModel.h"

namespace crayg {

class PolynomalOpticsCameraModel : public RealisticCameraModel {
  public:
    PolynomalOpticsCameraModel(Camera &camera, const Resolution &resolution);
    void init() override;
    std::optional<Ray> createPrimaryRay(float x, float y) override;

  private:
    float sensorOffset = 0;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMALOPTICSCAMERAMODEL_H_
