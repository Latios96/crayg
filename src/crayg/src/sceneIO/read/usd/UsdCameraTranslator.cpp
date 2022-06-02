//
// Created by Jan on 28.10.2021.
//

#include "basics/Transform.h"
#include "UsdCameraTranslator.h"
#include "UsdConversions.h"
#include "UsdUtils.h"
#include "Logger.h"

namespace crayg {

std::shared_ptr<Camera> UsdCameraTranslator::translate() {
    auto camera = BaseUsdXformableTranslator<pxr::UsdGeomCamera, Camera>::translate();

    const auto focalLength = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocalLengthAttr());
    camera->setFocalLength(focalLength);

    const auto filmbackSize = UsdUtils::getAttributeValueAs<float>(usdPrim.GetHorizontalApertureAttr());
    camera->setFilmbackSize(filmbackSize);

    return camera;
}
UsdCameraTranslator::UsdCameraTranslator(const pxr::UsdGeomCamera &camera) : BaseUsdXformableTranslator(camera) {

}
std::string UsdCameraTranslator::getTranslatedType() {
    return "camera";
};

}
