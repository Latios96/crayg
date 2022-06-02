//
// Created by Jan on 28.10.2021.
//

#include "basics/Transform.h"
#include "UsdCameraReader.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"
#include "Logger.h"

namespace crayg {

std::shared_ptr<Camera> UsdCameraReader::read() {
    auto camera = BaseUsdXformableReader<pxr::UsdGeomCamera, Camera>::read();

    const auto focalLength = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocalLengthAttr());
    camera->setFocalLength(focalLength);

    const auto filmbackSize = UsdUtils::getAttributeValueAs<float>(usdPrim.GetHorizontalApertureAttr());
    camera->setFilmbackSize(filmbackSize);

    return camera;
}
UsdCameraReader::UsdCameraReader(const pxr::UsdGeomCamera &camera) : BaseUsdXformableReader(camera) {

}
std::string UsdCameraReader::getTranslatedType() {
    return "camera";
};

}
