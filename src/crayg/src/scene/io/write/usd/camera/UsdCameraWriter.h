#pragma once

#include "scene/camera/Camera.h"
#include "scene/io/write/usd/base/BaseUsdTransformableWriter.h"
#include <pxr/usd/usdGeom/camera.h>

namespace crayg {

class UsdCameraWriter : public BaseUsdTransformableWriter<pxr::UsdGeomCamera, Camera> {
  public:
    UsdCameraWriter(Camera &craygObject);
    pxr::UsdGeomCamera write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;

  protected:
    std::string getTranslatedType() override;
    void writeLens(pxr::UsdGeomCamera camera);
};

}
