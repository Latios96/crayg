#include "scene/primitives/Sphere.h"
#include "sceneIO/read/usd/UsdStageReader.h"
#include <catch2/catch.hpp>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/editContext.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/pointInstancer.h>
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

        REQUIRE(scene.objects[0]->getMaterial()->getName() == "/material/shader");
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
                                                       IntegratorSettings(), IntersectorType::EMBREE,
                                                       BucketSequenceType::LINE_BY_LINE, BucketSamplerType::ADAPTIVE,
                                                       0.007f, 8, false, std::nullopt, ImageFormatWriteOptions{}));
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

    SECTION("providing a cameraName in UsdRenderSettings relation should use this camera") {
        SceneReader::ReadOptions readOptions;
        auto secondUsdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera2"));
        pxr::UsdGeomXformCommonAPI(secondUsdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));
        auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));
        usdRenderSettings.CreateCameraRel().AddTarget(secondUsdCamera.GetPath());

        UsdStageReader(*stage).readStageToScene(scene, readOptions);

        REQUIRE(scene.camera->getPosition() == Vector3f(1, 2, -3));
    }

    SECTION("providing a cameraName in translationOptions should take precedence over UsdRenderSettings relation use "
            "this camera") {
        SceneReader::ReadOptions readOptions;
        readOptions.cameraName = "/usdCamera2";
        auto secondUsdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera2"));
        pxr::UsdGeomXformCommonAPI(secondUsdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));
        auto thirdUsdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera3"));
        pxr::UsdGeomXformCommonAPI(thirdUsdCamera).SetTranslate(pxr::GfVec3f(4, 5, 6));
        auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));
        usdRenderSettings.CreateCameraRel().AddTarget(secondUsdCamera.GetPath());

        UsdStageReader(*stage).readStageToScene(scene, readOptions);

        REQUIRE(scene.camera->getPosition() == Vector3f(1, 2, -3));
    }

    SECTION("providing a non existent camera in UsdRenderSettings relation should throw exception") {
        stage->RemovePrim(pxr::SdfPath("/usdCamera"));
        SceneReader::ReadOptions readOptions;
        readOptions.cameraName = "/not_existing";

        REQUIRE_THROWS_MATCHES(UsdStageReader(*stage).readStageToScene(scene, readOptions), std::runtime_error,
                               Catch::Message("No camera with path /not_existing found in USD stage!"));
    }

    SECTION("should read point instancer") {
        auto proto = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/sphere"));
        auto usdGeomPointInstancer = pxr::UsdGeomPointInstancer::Define(stage, pxr::SdfPath("/usdGeomPointInstancer"));
        pxr::VtInt64Array ids({0, 1, 2});
        usdGeomPointInstancer.GetIdsAttr().Set(ids);
        pxr::VtIntArray protoIndices({0, 0, 0});
        usdGeomPointInstancer.GetProtoIndicesAttr().Set(protoIndices);
        usdGeomPointInstancer.GetPrototypesRel().AddTarget(pxr::SdfPath("/protos/sphere"));

        UsdStageReader(*stage).readStageToScene(scene);

        REQUIRE(scene.objects.size() == 1);
    }
}

TEST_CASE("UsdStageReader::applyVariantSets") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/usdCamera"));
    auto sphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/SphereGrp/Sphere"));
    sphere.CreateRadiusAttr().Clear();
    auto variantPrim = stage->GetPrimAtPath(pxr::SdfPath("/SphereGrp"));
    auto variantSet = variantPrim.GetVariantSets().AddVariantSet("myVariantSet");
    variantSet.AddVariant("small");
    variantSet.AddVariant("big");
    variantSet.SetVariantSelection("small");
    {
        pxr::UsdEditContext context(variantSet.GetVariantEditContext());
        sphere.GetRadiusAttr().Set(1.0);
    }
    variantSet.SetVariantSelection("big");
    {
        pxr::UsdEditContext context(variantSet.GetVariantEditContext());
        sphere.GetRadiusAttr().Set(10.0);
    }

    Scene scene;

    SECTION("not applying variant selection to stage should result in big sphere") {
        UsdStageReader(*stage).readStageToScene(scene);

        const auto sphere = std::dynamic_pointer_cast<Sphere>(scene.objects[0]);
        REQUIRE(sphere->getRadius() == 10);
    }

    SECTION("should apply variant selection to stage") {
        SceneReader::ReadOptions readOptions{};
        readOptions.variantSelections.push_back({"/SphereGrp", "myVariantSet", "small"});
        UsdStageReader(*stage).readStageToScene(scene, readOptions);

        const auto sphere = std::dynamic_pointer_cast<Sphere>(scene.objects[0]);
        REQUIRE(sphere->getRadius() == 1);
    }

    SECTION("should throw if invalid prim path was supplied") {
        SceneReader::ReadOptions readOptions{};
        readOptions.variantSelections.push_back({"/invalid", "myVariantSet", "small"});

        REQUIRE_THROWS_WITH(UsdStageReader(*stage).readStageToScene(scene, readOptions),
                            "Error when applying variant selections: invalid prim path /invalid.");
    }

    SECTION("should throw if invalid variant set name was supplied") {
        SceneReader::ReadOptions readOptions{};
        readOptions.variantSelections.push_back({"/SphereGrp", "invalid", "small"});

        REQUIRE_THROWS_WITH(UsdStageReader(*stage).readStageToScene(scene, readOptions),
                            "Error when applying variant selections: variant set with name 'invalid' does not exist on "
                            "prim /SphereGrp.");
    }

    SECTION("should throw if invalid variant name was supplied") {
        SceneReader::ReadOptions readOptions{};
        readOptions.variantSelections.push_back({"/SphereGrp", "myVariantSet", "invalid"});

        REQUIRE_THROWS_WITH(UsdStageReader(*stage).readStageToScene(scene, readOptions),
                            "Error when applying variant selections: variant with name 'invalid' does not exist on "
                            "variant set 'myVariantSet'on prim /SphereGrp.");
    }
}

}