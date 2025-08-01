#include "UsdCameraWriter.h"
#include "sceneIO/usd/UsdLensFileUtils.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

pxr::UsdGeomCamera UsdCameraWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdCamera = BaseUsdTransformableWriter::write(stage, usdPathFactory);

    usdCamera.GetFocalLengthAttr().Set(craygObject.getFocalLength());
    usdCamera.GetHorizontalApertureAttr().Set(craygObject.getFilmbackSize());
    usdCamera.GetFocusDistanceAttr().Set(craygObject.getFocusDistance());
    usdCamera.GetFStopAttr().Set(craygObject.getFStop());
    UsdUtils::createAndSetAttribute(usdCamera.GetPrim(), "craygCameraType", craygObject.getCameraType());

    if (craygObject.getCameraType() == CameraType::REALISTIC) {
        writeLens(usdCamera);
    }

    return usdCamera;
}

std::string UsdCameraWriter::getTranslatedType() {
    return "camera";
}

UsdCameraWriter::UsdCameraWriter(Camera &craygObject) : BaseUsdTransformableWriter(craygObject) {
}

void UsdCameraWriter::writeLens(pxr::UsdGeomCamera usdCamera) {
    UsdLensFileUtils::writeEmbeddedLensFile(craygObject.getLens(), usdCamera.GetPrim());
}

}