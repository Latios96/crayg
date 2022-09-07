#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include "BaseUsdXformableReader.h"
#include <pxr/usd/usdGeom/camera.h>
#include "scene/camera/Camera.h"


namespace crayg {

class UsdCameraReader : public BaseUsdXformableReader<pxr::UsdGeomCamera, Camera> {
 public:
    explicit UsdCameraReader(const pxr::UsdGeomCamera &camera);
    std::shared_ptr<Camera> read() override;
 protected:
    std::string getTranslatedType() override;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDCAMERATRANSLATOR_H_
