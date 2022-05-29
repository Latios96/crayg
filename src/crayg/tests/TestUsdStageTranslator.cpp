//
// Created by Jan on 28.10.2021.
//

#include <catch2/catch.hpp>
#include "sceneIO/read/usd/UsdStageTranslator.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdLux/sphereLight.h>
#include <pxr/usd/usdLux/rectLight.h>
#include <pxr/usd/usdLux/diskLight.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/usd/usdRender/settings.h>

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

        REQUIRE_THROWS_MATCHES(UsdStageTranslator(*stage).translateStageToScene(scene),
                               std::runtime_error,
                               Catch::Message("No camera found in USD stage!"));
    }

    SECTION("should translate sphereLight") {
        auto usdSphereLight = pxr::UsdLuxSphereLight::Define(stage, pxr::SdfPath("/usdSphereLight"));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.lights.size() == 1);
    }

    SECTION("should translate rectLight") {
        auto usdRectLight = pxr::UsdLuxRectLight::Define(stage, pxr::SdfPath("/usdRectLight"));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.lights.size() == 1);
    }

    SECTION("should translate mesh") {
        auto usdMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.owningObjects.size() == 1);
    }

    SECTION("should not override material for mesh") {
        auto usdMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        auto usdShadeMaterial = pxr::UsdShadeMaterial::Define(stage, pxr::SdfPath("/material"));
        auto usdShadeShader = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/material/shader"));
        pxr::UsdShadeMaterialBindingAPI bindingApi(usdMesh.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeShader.CreateInput(pxr::TfToken("diffuseColor"),
                                   pxr::SdfValueTypeNames->Color3f).Set(pxr::GfVec3f(0.5f));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.owningObjects[0]->getMaterial()->getName()=="/material");
    }

    SECTION("should translate sphere") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.owningObjects.size() == 1);
    }

    SECTION("should translate disklight") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.lights.size() == 1);
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

    SECTION("should translate hidden rectLight") {
        auto usdRectLight = pxr::UsdLuxRectLight::Define(stage, pxr::SdfPath("/usdRectLight"));
        usdRectLight.MakeInvisible();

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.lights.size() == 0);
    }

    SECTION("should not translate hidden sphere") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));
        usdSphere.MakeInvisible();

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.owningObjects.size() == 0);
    }

    SECTION("should not translate hidden disklight") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));
        usdDiskLight.MakeInvisible();

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.lights.size() == 0);
    }

    SECTION("should create default rendersettings if there are no rendersettings in the stage") {
        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.renderSettings == RenderSettings(Resolution(1280, 720), 4));
    }

    SECTION("should read rendersettings if defined") {
        auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));
        usdRenderSettings.GetResolutionAttr().Set(pxr::GfVec2i(800, 600));
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("maxSamples"), pxr::SdfValueTypeNames->Int).Set(2);

        UsdStageTranslator(*stage).translateStageToScene(scene);

        REQUIRE(scene.renderSettings == RenderSettings(Resolution(800, 600), 2));
    }

    SECTION("providing a cameraName in translationOptions should use this camera") {
        SceneReader::ReadOptions readOptions;
        readOptions.cameraName = "/usdCamera2";
        auto secondsUsdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera2"));
        pxr::UsdGeomXformCommonAPI(secondsUsdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdStageTranslator(*stage).translateStageToScene(scene, readOptions);

        REQUIRE(scene.camera->getPosition() == Vector3f(1, 2, -3));
    }

    SECTION("providing a non existent camera path should throw exception") {
        stage->RemovePrim(pxr::SdfPath("/usdCamera"));
        SceneReader::ReadOptions readOptions;
        readOptions.cameraName = "/not_existing";

        REQUIRE_THROWS_MATCHES(UsdStageTranslator(*stage).translateStageToScene(scene, readOptions),
                               std::runtime_error,
                               Catch::Message("No camera with path /not_existing found in USD stage!"));
    }

}

}