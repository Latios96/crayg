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
    auto camera = BaseUsdTranslator<pxr::UsdGeomCamera, Camera>::translate();

    const pxr::GfMatrix4d matrix = usdPrim.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default());

    const Vector3f position = UsdConversions::convert(matrix.ExtractTranslation());
    camera->setPosition(position);

    const auto focalLength = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocalLengthAttr());
    camera->setFocalLength(focalLength);

    const auto filmbackSize = UsdUtils::getAttributeValueAs<float>(usdPrim.GetHorizontalApertureAttr());
    camera->setFilmbackSize(filmbackSize);

    const auto focusDistance = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocusDistanceAttr());
    const Vector3f centerOfInterest =
        Transform(UsdConversions::convert(matrix)).apply(Vector3f(0, 0, (focusDistance != 0 ? focusDistance : 1)));
    camera->setCenterOfInterest(centerOfInterest);

    camera->setUserUpVector({0, 1, 0});

    return camera;
}
UsdCameraTranslator::UsdCameraTranslator(const pxr::UsdGeomCamera &camera) : BaseUsdTranslator(camera) {

}
std::string UsdCameraTranslator::getTranslatedType() {
    return "camera";
};

}
