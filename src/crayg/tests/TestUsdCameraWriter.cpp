//
// Created by Jan on 28.10.2021.
//


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
        auto myCamera = std::make_shared<Camera>(Transform::withPosition({1, 2, 3}),
                                                 50.0f,
                                                 35.0f);

        UsdCameraWriter usdCameraWriter(myCamera);
        usdCameraWriter.write(stage, usdPathFactory);

        auto usdGeomCamera = pxr::UsdGeomCamera(stage->GetPrimAtPath(pxr::SdfPath("/camera0")));
        auto focalLength = UsdUtils::getAttributeValueAs<float>(usdGeomCamera.GetFocalLengthAttr());
        auto horizontalAperture = UsdUtils::getAttributeValueAs<float>(usdGeomCamera.GetHorizontalApertureAttr());
        REQUIRE(focalLength == 50.0f);
        REQUIRE(horizontalAperture == 35.0f);
        REQUIRE(usdGeomCamera.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation()
                    == pxr::GfVec3f(1, 2, -3));
    }

}

}