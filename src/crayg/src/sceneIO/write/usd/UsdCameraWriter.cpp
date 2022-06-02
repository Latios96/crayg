//
// Created by Jan on 02.06.2022.
//

#include "UsdCameraWriter.h"
#include "sceneIO/usd/UsdConversions.h"
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

pxr::UsdGeomCamera UsdCameraWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdCamera = BaseUsdWriter::write(stage, usdPathFactory);
    // todo author xform
    usdCamera.GetFocalLengthAttr().Set(craygObject->getFocalLength());
    usdCamera.GetHorizontalApertureAttr().Set(craygObject->getFilmbackSize());

    return usdCamera;
}

std::string UsdCameraWriter::getTranslatedType() {
    return "camera";
}
UsdCameraWriter::UsdCameraWriter(const std::shared_ptr<Camera> &craygObject) : BaseUsdWriter(craygObject) {}

} // crayg