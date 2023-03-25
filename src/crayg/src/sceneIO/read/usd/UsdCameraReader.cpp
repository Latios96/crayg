#include "UsdCameraReader.h"
#include "basics/Transform.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

std::shared_ptr<Camera> UsdCameraReader::read() {
    auto camera = BaseUsdXformableReader<pxr::UsdGeomCamera, Camera>::read();

    const auto focalLength = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocalLengthAttr(), this->timeCodeToRead);
    camera->setFocalLength(focalLength);

    const auto filmbackSize =
        UsdUtils::getAttributeValueAs<float>(usdPrim.GetHorizontalApertureAttr(), this->timeCodeToRead);
    camera->setFilmbackSize(filmbackSize);

    const auto cameraType =
        UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "craygCameraType", CameraType::PINE_HOLE);
    camera->setCameraType(cameraType);

    const auto focusDistance =
        UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocusDistanceAttr(), this->timeCodeToRead);
    camera->setFocusDistance(focusDistance);

    const auto fStop = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFStopAttr(), this->timeCodeToRead);
    camera->setFStop(fStop);

    return camera;
}

UsdCameraReader::UsdCameraReader(const pxr::UsdGeomCamera &camera) : BaseUsdXformableReader(camera) {
}

std::string UsdCameraReader::getTranslatedType() {
    return "camera";
};

}
