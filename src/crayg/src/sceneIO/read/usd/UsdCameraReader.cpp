#include "UsdCameraReader.h"
#include "Logger.h"
#include "basics/Transform.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

std::shared_ptr<Camera> UsdCameraReader::read() {
    auto camera = BaseUsdXformableReader<pxr::UsdGeomCamera, Camera>::read();

    const auto focalLength = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocalLengthAttr(), this->timeCodeToRead);
    camera->setFocalLength(focalLength);

    const auto filmbackSize =
        UsdUtils::getAttributeValueAs<float>(usdPrim.GetHorizontalApertureAttr(), this->timeCodeToRead);
    camera->setFilmbackSize(filmbackSize);

    return camera;
}

UsdCameraReader::UsdCameraReader(const pxr::UsdGeomCamera &camera) : BaseUsdXformableReader(camera) {
}

std::string UsdCameraReader::getTranslatedType() {
    return "camera";
};

}
