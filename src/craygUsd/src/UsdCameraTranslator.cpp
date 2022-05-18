//
// Created by Jan on 28.10.2021.
//

#include <basics/Transform.h>
#include "UsdCameraTranslator.h"
#include "UsdConversions.h"
#include "UsdUtils.h"
#include "Logger.h"

namespace crayg {

UsdCameraTranslator::UsdCameraTranslator(const pxr::UsdGeomCamera &camera) : usdCamera(camera) {}

std::shared_ptr<Camera> UsdCameraTranslator::translate() {
    Logger::debug("Translating camera {}", usdCamera.GetPath().GetString());

    const pxr::GfMatrix4d matrix = usdCamera.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default());

    const Vector3f position = UsdConversions::convert(matrix.ExtractTranslation());

    const auto focalLength = UsdUtils::getAttributeValueAs<float>(usdCamera.GetFocalLengthAttr());
    const auto filmbackSize = UsdUtils::getAttributeValueAs<float>(usdCamera.GetHorizontalApertureAttr());
    const auto focusDistance = UsdUtils::getAttributeValueAs<float>(usdCamera.GetFocusDistanceAttr());
    const Vector3f centerOfInterest =
        Transform(UsdConversions::convert(matrix)).apply(Vector3f(0, 0, (focusDistance != 0 ? focusDistance : 1)));

    return std::make_shared<Camera>(position, Vector3f(0, 1, 0), centerOfInterest, focalLength, filmbackSize);
};

}
