//
// Created by Jan on 28.10.2021.
//


#include <catch2/catch.hpp>
#include "UsdStageTranslator.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdLux/sphereLight.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("UsdStageTranslator/translateStageToScene") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera"));
    Scene scene;

    SECTION("should translate stage with camera") {
        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.camera != nullptr);
    }

    SECTION("not providing a specific camera should default to the first one") {
        auto secondsUsdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera2"));
        pxr::UsdGeomXformCommonAPI(secondsUsdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.camera->getPosition() == Vector3f(0, 0, 0));
    }

    SECTION("translating a stage without camera should throw exception") {
        stage->RemovePrim(pxr::SdfPath("/usdCamera"));

        REQUIRE_THROWS_AS(UsdStageTranslator(*stage).translateStageToScene(scene), std::runtime_error);
    }

    SECTION("should translate sphereLight") {
        auto usdSphereLight = pxr::UsdLuxSphereLight::Define(stage, pxr::SdfPath("/usdSphereLight"));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.lights.size() == 1);
    }

    SECTION("should translate mesh") {
        auto usdMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.owningObjects.size() == 1);
    }

    SECTION("should not translate hidden sphereLight") {
        auto usdSphereLight = pxr::UsdLuxSphereLight::Define(stage, pxr::SdfPath("/usdSphereLight"));
        usdSphereLight.MakeInvisible();

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.lights.size() == 0);
    }

    SECTION("should not translate hidden mesh") {
        auto usdMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        usdMesh.MakeInvisible();

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.owningObjects.size() == 0);
    }

    SECTION("not providing render settings should create defaults") {
        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.renderSettings == RenderSettings(Resolution(1280, 720), 4));
    }

    SECTION("providing renderSettings in translationOptions should use them") {
        UsdStageTranslator::TranslationsOptions translationsOptions;
        translationsOptions.renderSettings.emplace(Resolution(800, 600), 1);

        UsdStageTranslator(*stage).translateStageToScene(scene, translationsOptions);

        REQUIRE(scene.renderSettings == RenderSettings(Resolution(800, 600), 1));
    }

}

}