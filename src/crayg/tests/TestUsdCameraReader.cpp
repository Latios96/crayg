#include <catch2/catch.hpp>
#include "sceneIO/read/usd/UsdCameraReader.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <iostream>

namespace crayg {

TEST_CASE("CameraReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera"));

    SECTION("should read fully populated camera correctly") {
        pxr::UsdGeomXformCommonAPI(usdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdCamera.GetFocusDistanceAttr().Set(5.0f);
        usdCamera.GetFocalLengthAttr().Set(35.0f);
        usdCamera.GetHorizontalApertureAttr().Set(36.0f);

        UsdCameraReader usdCameraReader(usdCamera);
        auto camera = usdCameraReader.read();

        auto expectedCamera = std::make_shared<crayg::Camera>(Transform::withPosition({1, 2, -3}),
                                                              35,
                                                              36);
        REQUIRE(*camera == *expectedCamera);
    }

    SECTION("should read camera with translation on its parents correctly") {
        auto parent = pxr::UsdGeomXform::Define(stage, pxr::SdfPath("/cam_grp"));
        pxr::UsdGeomXformCommonAPI(parent).SetScale(pxr::GfVec3f(1, 2, 3));
        pxr::UsdGeomXformCommonAPI(usdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdCameraReader usdCameraReader(usdCamera);
        auto camera = usdCameraReader.read();

        REQUIRE(camera->getPosition() == Vector3f(1, 2, -3));
    }

    SECTION("should read fully populated camera with time samples correctly") {
        pxr::UsdGeomXformCommonAPI(usdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3), pxr::UsdTimeCode());
        usdCamera.GetFocusDistanceAttr().Set(5.0f, pxr::UsdTimeCode());
        usdCamera.GetFocalLengthAttr().Set(35.0f, pxr::UsdTimeCode());
        usdCamera.GetHorizontalApertureAttr().Set(36.0f, pxr::UsdTimeCode());

        UsdCameraReader usdCameraReader(usdCamera);
        auto camera = usdCameraReader.read();

        auto expectedCamera = std::make_shared<crayg::Camera>(Transform::withPosition({1, 2, -3}),
                                                              35,
                                                              36);
        REQUIRE(*camera == *expectedCamera);
    }

}

}