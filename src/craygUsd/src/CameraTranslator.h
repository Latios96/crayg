//
// Created by Jan on 28.10.2021.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_CAMERATRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_CAMERATRANSLATOR_H_
#include <pxr/usd/usdGeom/camera.h>
#include <scene/Camera.h>

namespace crayg {

class CameraTranslator {
 public:
    explicit CameraTranslator(pxr::UsdGeomCamera camera);
    std::shared_ptr<Camera> translate();
 private:
    pxr::UsdGeomCamera usdCamera;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_CAMERATRANSLATOR_H_
