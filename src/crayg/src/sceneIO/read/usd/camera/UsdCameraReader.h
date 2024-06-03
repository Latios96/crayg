#pragma once

#include "scene/camera/Camera.h"
#include "sceneIO/read/usd/base/BaseUsdXformableReader.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdGeom/camera.h>

namespace crayg {

class UsdCameraReader : public BaseUsdXformableReader<pxr::UsdGeomCamera, Camera> {
  public:
    explicit UsdCameraReader(const pxr::UsdGeomCamera &camera);
    std::shared_ptr<Camera> read() override;

  protected:
    std::string getTranslatedType() override;
    void readCameraLens(std::shared_ptr<Camera> &camera) const;
};

}
