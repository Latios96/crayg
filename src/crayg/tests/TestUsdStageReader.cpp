#include "sceneIO/read/usd/UsdStageReader.h"
#include <catch2/catch.hpp>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/usd/usdLux/diskLight.h>
#include <pxr/usd/usdLux/rectLight.h>
#include <pxr/usd/usdLux/sphereLight.h>
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

TEST_CASE("UsdStageReader::readStageToScene") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera"));
    Scene scene;

    SECTION("should read stage with camera") {
        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.camera != nullptr);
    }

    SECTION("not providing a specific camera should default to the first one") {
        auto secondsUsdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera2"));
        pxr::UsdGeomXformCommonAPI(secondsUsdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.camera->getPosition() == Vector3f(0, 0, 0));
    }

    SECTION("translating a stage without camera should throw exception") {
        stage->RemovePrim(pxr::SdfPath("/usdCamera"));

        REQUIRE_THROWS_MATCHES(UsdStageReader(*stage).readStageToScene(scene), std::runtime_error,
                               Catch::Message("No camera found in USD stage!"));
    }

    SECTION("should read sphereLight") {
        auto usdSphereLight = pxr::UsdLuxSphereLight::Define(stage, pxr::SdfPath("/usdSphereLight"));

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.lights.size() == 1);
    }

    SECTION("should read rectLight") {
        auto usdRectLight = pxr::UsdLuxRectLight::Define(stage, pxr::SdfPath("/usdRectLight"));

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.lights.size() == 1);
    }

    SECTION("should read mesh") {
        auto usdMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.objects.size() == 1);
    }

    SECTION("should read subdivision surface") {
        auto usdMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        usdMesh.GetSubdivisionSchemeAttr().Set(pxr::UsdGeomTokens->catmullClark);

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.objects.size() == 1);
    }

    SECTION("should read instance") {
        auto instanceSourcePrim = stage->OverridePrim(pxr::SdfPath("/InstanceSources"));
        auto instancedContent = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/InstanceSources/source"));
        instanceSourcePrim.SetSpecifier(pxr::SdfSpecifierOver);

        for (int i = 0; i < 2; i++) {
            auto instance = stage->DefinePrim(pxr::SdfPath(fmt::format("/instance{}", i)));
            instance.GetReferences().AddReference(pxr::SdfReference("", pxr::SdfPath("/InstanceSources/source")));
            instance.SetInstanceable(true);
        }

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.objects.size() == 2);
    }

    SECTION("should not override material for mesh") {
        auto usdMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        auto usdShadeMaterial = pxr::UsdShadeMaterial::Define(stage, pxr::SdfPath("/material"));
        auto usdShadeShader = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/material/shader"));
        pxr::UsdShadeMaterialBindingAPI bindingApi(usdMesh.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeShader.CreateInput(pxr::TfToken("diffuseColor"), pxr::SdfValueTypeNames->Color3f)
            .Set(pxr::GfVec3f(0.5f));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.objects[0]->getMaterial()->getName() == "/material");
    }

    SECTION("should read sphere") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.objects.size() == 1);
    }

    SECTION("should read disklight") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.lights.size() == 1);
    }

    SECTION("should not read hidden sphereLight") {
        auto usdSphereLight = pxr::UsdLuxSphereLight::Define(stage, pxr::SdfPath("/usdSphereLight"));
        usdSphereLight.MakeInvisible();

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.lights.size() == 0);
    }

    SECTION("should not read hidden mesh") {
        auto usdMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        usdMesh.MakeInvisible();

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.objects.size() == 0);
    }

    SECTION("should read hidden rectLight") {
        auto usdRectLight = pxr::UsdLuxRectLight::Define(stage, pxr::SdfPath("/usdRectLight"));
        usdRectLight.MakeInvisible();

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.lights.size() == 0);
    }

    SECTION("should not read hidden sphere") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));
        usdSphere.MakeInvisible();

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.objects.size() == 0);
    }

    SECTION("should not read hidden disklight") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));
        usdDiskLight.MakeInvisible();

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.lights.size() == 0);
    }

    SECTION("should create default rendersettings if there are no rendersettings in the stage") {
        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.renderSettings == RenderSettings::createDefault());
    }

    SECTION("should read rendersettings if defined") {
        auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));
        usdRenderSettings.GetResolutionAttr().Set(pxr::GfVec2i(800, 600));
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("maxSamples"), pxr::SdfValueTypeNames->Int).Set(2);

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.renderSettings == RenderSettings(Resolution(800, 600), 2, IntegratorType::RAYTRACING,
                                                       IntegratorSettings(), IntersectorType::EMBREE));
    }

    SECTION("providing a cameraName in translationOptions should use this camera") {
        SceneReader::ReadOptions readOptions;
        readOptions.cameraName = "/usdCamera2";
        auto secondsUsdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera2"));
        pxr::UsdGeomXformCommonAPI(secondsUsdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdStageReader(*stage).readStageToScene(scene, readOptions);

        REQUIRE(scene.camera->getPosition() == Vector3f(1, 2, -3));
    }

    SECTION("providing a non existent camera path should throw exception") {
        stage->RemovePrim(pxr::SdfPath("/usdCamera"));
        SceneReader::ReadOptions readOptions;
        readOptions.cameraName = "/not_existing";

        REQUIRE_THROWS_MATCHES(UsdStageReader(*stage).readStageToScene(scene, readOptions), std::runtime_error,
                               Catch::Message("No camera with path /not_existing found in USD stage!"));
    }
}

}