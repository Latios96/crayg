#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/UsdCameraWriter.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("UsdCameraReader::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write camera correctly") {
        Camera myCamera(Transform::withPosition({1, 2, 3}), 50.0f, 35.0f);
        myCamera.setFocusDistance(50.f);
        myCamera.setFStop(2.8f);
        myCamera.setCameraType(CameraType::REALISTIC);
        CameraLens cameraLens("Canon", {{1.f, 2.f, 3.f, 4.f}});
        myCamera.lens = std::make_unique<CameraLens>(cameraLens);

        UsdCameraWriter usdCameraWriter(myCamera);
        usdCameraWriter.write(stage, usdPathFactory);

        auto usdGeomCamera = pxr::UsdGeomCamera(stage->GetPrimAtPath(pxr::SdfPath("/camera0")));
        auto focalLength = UsdUtils::getStaticAttributeValueAs<float>(usdGeomCamera.GetFocalLengthAttr());
        auto horizontalAperture = UsdUtils::getStaticAttributeValueAs<float>(usdGeomCamera.GetHorizontalApertureAttr());
        auto focusDistance = UsdUtils::getStaticAttributeValueAs<float>(usdGeomCamera.GetFocusDistanceAttr());
        auto fStop = UsdUtils::getStaticAttributeValueAs<float>(usdGeomCamera.GetFStopAttr());
        auto cameraType = UsdUtils::getAttributeValueAsEnum<CameraType>(usdGeomCamera.GetPrim(), "craygCameraType",
                                                                        CameraType::THIN_LENS);

        REQUIRE(focalLength == 50.0f);
        REQUIRE(horizontalAperture == 35.0f);
        REQUIRE(focusDistance == 50.f);
        REQUIRE(fStop == 2.8f);
        REQUIRE(cameraType == CameraType::REALISTIC);
        REQUIRE(usdGeomCamera.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation() ==
                pxr::GfVec3f(1, 2, -3));
        REQUIRE(usdGeomCamera.GetPrim()
                    .GetAttribute(pxr::TfToken("craygLensFile"))
                    .GetCustomDataByKey(pxr::TfToken("lens"))
                    .CanCast<pxr::VtDictionary>());
    }
}

}