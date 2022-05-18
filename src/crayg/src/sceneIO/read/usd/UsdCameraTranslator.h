//
// Created by Jan on 28.10.2021.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_

#include "CraygUsdBase.h"
#include <pxr/usd/usdGeom/camera.h>
#include "scene/Camera.h"

namespace crayg {

class UsdCameraTranslator {
 public:
    explicit UsdCameraTranslator(const pxr::UsdGeomCamera &camera);
    std::shared_ptr<Camera> translate();
 private:
    pxr::UsdGeomCamera usdCamera;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_
