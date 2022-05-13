//
// Created by Jan on 28.10.2021.
//


#include <catch2/catch.hpp>
#include <UsdCameraTranslator.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <iostream>

namespace crayg {

TEST_CASE("CameraTranslatorTranslate") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera"));

    SECTION("should translate fully populated camera correctly") {
        pxr::UsdGeomXformCommonAPI(usdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdCamera.GetFocusDistanceAttr().Set(5.0f);
        usdCamera.GetFocalLengthAttr().Set(35.0f);
        usdCamera.GetHorizontalApertureAttr().Set(36.0f);

        UsdCameraTranslator cameraTranslator(usdCamera);
        auto camera = cameraTranslator.translate();

        auto expectedCamera = std::make_shared<crayg::Camera>(crayg::Vector3f(1, 2, -3),
                                                              crayg::Vector3f(0, 1, 0),
                                                              crayg::Vector3f(1, 2, 2),
                                                              35,
                                                              36);
        REQUIRE(*camera == *expectedCamera);
    }

    SECTION("should translate fully populated camera correctly") {
        pxr::UsdGeomXformCommonAPI(usdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdCamera.GetFocalLengthAttr().Set(35.0f);
        usdCamera.GetHorizontalApertureAttr().Set(36.0f);

        UsdCameraTranslator cameraTranslator(usdCamera);
        auto camera = cameraTranslator.translate();

        auto expectedCamera = std::make_shared<crayg::Camera>(crayg::Vector3f(1, 2, -3),
                                                              crayg::Vector3f(0, 1, 0),
                                                              crayg::Vector3f(1, 2, -2),
                                                              35,
                                                              36);
        REQUIRE(*camera == *expectedCamera);
    }

}

}