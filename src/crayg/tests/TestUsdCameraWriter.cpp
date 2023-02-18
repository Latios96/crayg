#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/UsdCameraWriter.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

TEST_CASE("UsdCameraReader::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write camera correctly") {
        Camera myCamera(Transform::withPosition({1, 2, 3}),
                        50.0f,
                        35.0f);

        UsdCameraWriter usdCameraWriter(myCamera);
        usdCameraWriter.write(stage, usdPathFactory);

        auto usdGeomCamera = pxr::UsdGeomCamera(stage->GetPrimAtPath(pxr::SdfPath("/camera0")));
        auto focalLength = UsdUtils::getStaticAttributeValueAs<float>(usdGeomCamera.GetFocalLengthAttr());
        auto horizontalAperture = UsdUtils::getStaticAttributeValueAs<float>(usdGeomCamera.GetHorizontalApertureAttr());
        REQUIRE(focalLength == 50.0f);
        REQUIRE(horizontalAperture == 35.0f);
        REQUIRE(usdGeomCamera.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation()
                    == pxr::GfVec3f(1, 2, -3));
    }

}

}