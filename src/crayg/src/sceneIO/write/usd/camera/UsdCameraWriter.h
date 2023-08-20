#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_

#include "scene/camera/Camera.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/write/usd/base/BaseUsdTransformableWriter.h"
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

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_
