#include "fixtures/TemporaryDirectory.h"
#include "sceneIO/read/usd/UsdCameraReader.h"
#include "sceneIO/usd/UsdLensFileUtils.h"
#include "sceneIO/usd/UsdUtils.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("CameraReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera"));

    SECTION("should read fully populated camera correctly") {
        pxr::UsdGeomXformCommonAPI(usdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdCamera.GetFocusDistanceAttr().Set(5.0f);
        usdCamera.GetFocalLengthAttr().Set(35.0f);
        usdCamera.GetHorizontalApertureAttr().Set(36.0f);
        usdCamera.GetFocusDistanceAttr().Set(50.0f);
        usdCamera.GetFStopAttr().Set(2.8f);
        UsdUtils::createAndSetAttribute(usdCamera.GetPrim(), "craygCameraType", CameraType::THIN_LENS);

        UsdCameraReader usdCameraReader(usdCamera);
        auto camera = usdCameraReader.read();

        auto expectedCamera = std::make_shared<crayg::Camera>(Transform::withPosition({1.f, 2.f, -3.f}), 35.f, 36.f);
        expectedCamera->setName("/usdCamera");
        expectedCamera->setFocusDistance(50.f);
        expectedCamera->setFStop(2.8f);
        expectedCamera->setCameraType(CameraType::THIN_LENS);
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
        usdCamera.GetFocalLengthAttr().Set(35.0f, pxr::UsdTimeCode());
        usdCamera.GetHorizontalApertureAttr().Set(36.0f, pxr::UsdTimeCode());

        UsdCameraReader usdCameraReader(usdCamera);
        auto camera = usdCameraReader.read();

        auto expectedCamera = std::make_shared<crayg::Camera>(Transform::withPosition({1.f, 2.f, -3.f}), 35.f, 36.f);
        expectedCamera->setName("/usdCamera");
        REQUIRE(*camera == *expectedCamera);
    }
    SECTION("cameraType should default to PineHoleCamera") {
        UsdCameraReader usdCameraReader(usdCamera);
        auto camera = usdCameraReader.read();

        REQUIRE(camera->getCameraType() == CameraType::PINE_HOLE);
    }

    SECTION("should require lens file when reading realistic lens") {
        UsdCameraReader usdCameraReader(usdCamera);
        UsdUtils::createAndSetAttribute(usdCamera.GetPrim(), "craygCameraType", CameraType::REALISTIC);

        REQUIRE_THROWS_WITH(usdCameraReader.read(), "craygLensFile attribute was not authored for camera /usdCamera");
    }

    SECTION("should read camera with lens file successfully") {
        TemporaryDirectory temporaryDirectory;
        auto lensFilePath = temporaryDirectory.writeToFile("lensfile.txt", R"(# a header comment
3
1 2 3 4
5 6 7 8)");
        UsdCameraReader usdCameraReader(usdCamera);
        UsdUtils::createAndSetAttribute(usdCamera.GetPrim(), "craygCameraType", CameraType::REALISTIC);
        UsdUtils::createAndSetAttribute(usdCamera.GetPrim(), "craygLensFile", lensFilePath);

        auto camera = usdCameraReader.read();

        REQUIRE(camera->getCameraType() == CameraType::REALISTIC);
        REQUIRE(camera->getLens() ==
                CameraLens("", std::vector<LensElement>({{0.1, 0.2, 3, 0.2}, {0.5, 0.6, 7, 0.4}})));
    }

    SECTION("should read embedded lens file successfully") {
        CameraLens cameraLens("Canon 70-200", {{1, 2, 3, 4}, {4, 5, 6, 7}});
        UsdUtils::createAndSetAttribute(usdCamera.GetPrim(), "craygCameraType", CameraType::REALISTIC);
        UsdLensFileUtils::writeEmbeddedLensFile(cameraLens, usdCamera.GetPrim());
        UsdCameraReader usdCameraReader(usdCamera);

        auto camera = usdCameraReader.read();

        REQUIRE(camera->getCameraType() == CameraType::REALISTIC);
        REQUIRE(camera->getLens() == CameraLens("Canon 70-200", {{1, 2, 3, 4}, {4, 5, 6, 7}}));
    }
}

}