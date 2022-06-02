//
// Created by Jan on 02.06.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdGeom/camera.h>
#include "scene/Camera.h"
#include "BaseUsdWriter.h"

namespace crayg {

class UsdCameraWriter : public BaseUsdWriter<pxr::UsdGeomCamera, Camera> {
 public:
    UsdCameraWriter(const std::shared_ptr<Camera> &craygObject);
    pxr::UsdGeomCamera write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
 protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDCAMERAWRITER_H_
