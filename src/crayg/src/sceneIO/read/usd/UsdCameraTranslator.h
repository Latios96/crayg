//
// Created by Jan on 28.10.2021.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_

#include "sceneIO/CraygUsdBase.h"
#include "BaseUsdXformableTranslator.h"
#include <pxr/usd/usdGeom/camera.h>
#include "scene/Camera.h"


namespace crayg {

class UsdCameraTranslator : public BaseUsdXformableTranslator<pxr::UsdGeomCamera, Camera> {
 public:
    explicit UsdCameraTranslator(const pxr::UsdGeomCamera &camera);
    std::shared_ptr<Camera> translate() override;
 protected:
    std::string getTranslatedType() override;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_
