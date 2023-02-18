#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdGeom/camera.h>
#include "scene/camera/Camera.h"
#include "BaseUsdTransformableWriter.h"

namespace crayg {

class UsdCameraWriter : public BaseUsdTransformableWriter<pxr::UsdGeomCamera, Camera> {
 public:
    UsdCameraWriter(Camera &craygObject);
    pxr::UsdGeomCamera write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
 protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_
