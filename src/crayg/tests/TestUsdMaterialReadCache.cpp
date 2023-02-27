#include "scene/materials/Material.h"
#include "scene/materials/UsdPreviewSurface.h"
#include "sceneIO/read/usd/UsdMaterialReadCache.h"
#include <catch2/catch.hpp>
#include <pxr/base/gf/vec3f.h>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>

namespace crayg {

bool isDefaultMaterial(const std::shared_ptr<Material> &material) {
    return material->getName() == "defaultMaterial" && material->getType() == "UsdPreviewSurface";
}

std::shared_ptr<UsdPreviewSurface> getAsUsdPreviewSurface(const std::shared_ptr<Material> &material) {
    if (material->getType() != "UsdPreviewSurface") {
        throw std::runtime_error("This is not a UsdPreviewSurface.");
    }
    return std::static_pointer_cast<UsdPreviewSurface>(material);
}

TEST_CASE("UsdMaterialReadCache::getCachedReadPrimMaterial") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto geo = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
    auto usdShadeMaterial = pxr::UsdShadeMaterial::Define(stage, pxr::SdfPath("/material"));
    auto usdShadeShader = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/material/shader"));

    SECTION("no assigned material should read to default Material") {
        UsdMaterialReadCache usdMaterialReadCache;

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(isDefaultMaterial(material));
    }

    SECTION("default material should be cached if no material is assigned") {
        UsdMaterialReadCache usdMaterialReadCache;

        auto material1 = usdMaterialReadCache.getCachedReadPrimMaterial(geo);
        auto material2 = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(isDefaultMaterial(material1));
        REQUIRE(material1 == material2);
    }

    SECTION("assigned material that has no surface shader should read to default Material") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(isDefaultMaterial(material));
    }

    SECTION("default material should be cached if material has no surface shader") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);

        auto material1 = usdMaterialReadCache.getCachedReadPrimMaterial(geo);
        auto material2 = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(isDefaultMaterial(material1));
        REQUIRE(material1 == material2);
    }

    SECTION("assigned material that has not a UsdPreviewSurface as surface shader should read to default Material") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("test")));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(isDefaultMaterial(material));
    }

    SECTION("default material should be cached if not a UsdPreviewSurface is assigned") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("test")));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));

        auto material1 = usdMaterialReadCache.getCachedReadPrimMaterial(geo);
        auto material2 = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(isDefaultMaterial(material1));
        REQUIRE(material1 == material2);
    }

    SECTION("assigned authored UsdPreviewSurface should read to correct shader") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeShader.CreateInput(pxr::TfToken("diffuseColor"), pxr::SdfValueTypeNames->Color3f)
            .Set(pxr::GfVec3f(1, 2, 3));
        usdShadeShader.CreateInput(pxr::TfToken("emissiveColor"), pxr::SdfValueTypeNames->Color3f)
            .Set(pxr::GfVec3f(4, 5, 6));
        usdShadeShader.CreateInput(pxr::TfToken("useSpecularWorkflow"), pxr::SdfValueTypeNames->Int).Set(1);
        usdShadeShader.CreateInput(pxr::TfToken("specularColor"), pxr::SdfValueTypeNames->Color3f)
            .Set(pxr::GfVec3f(7, 8, 9));
        usdShadeShader.CreateInput(pxr::TfToken("metallic"), pxr::SdfValueTypeNames->Float).Set(0.1f);
        usdShadeShader.CreateInput(pxr::TfToken("roughness"), pxr::SdfValueTypeNames->Float).Set(0.2f);
        usdShadeShader.CreateInput(pxr::TfToken("clearcoat"), pxr::SdfValueTypeNames->Float).Set(0.3f);
        usdShadeShader.CreateInput(pxr::TfToken("clearcoatRoughness"), pxr::SdfValueTypeNames->Float).Set(0.4f);
        usdShadeShader.CreateInput(pxr::TfToken("opacity"), pxr::SdfValueTypeNames->Float).Set(0.5f);
        usdShadeShader.CreateInput(pxr::TfToken("opacityThreshold"), pxr::SdfValueTypeNames->Float).Set(0.6f);
        usdShadeShader.CreateInput(pxr::TfToken("ior"), pxr::SdfValueTypeNames->Float).Set(0.7f);
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(material->getName() == "/material");
        const auto usdPreviewSurface = getAsUsdPreviewSurface(material);
        REQUIRE(usdPreviewSurface->diffuseColor == Color(1, 2, 3));
        REQUIRE(usdPreviewSurface->emissiveColor == Color(4, 5, 6));
        REQUIRE(usdPreviewSurface->useSpecularWorkflow == true);
        REQUIRE(usdPreviewSurface->specularColor == Color(7, 8, 9));
        REQUIRE(usdPreviewSurface->metallic == 0.1f);
        REQUIRE(usdPreviewSurface->roughness == 0.2f);
        REQUIRE(usdPreviewSurface->clearcoat == 0.3f);
        REQUIRE(usdPreviewSurface->clearcoatRoughness == 0.4f);
        REQUIRE(usdPreviewSurface->opacity == 0.5f);
        REQUIRE(usdPreviewSurface->opacityThreshold == 0.6f);
        REQUIRE(usdPreviewSurface->ior == 0.7f);
    }

    SECTION("UsdPreviewSurface translation should be cached") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeShader.CreateInput(pxr::TfToken("diffuseColor"), pxr::SdfValueTypeNames->Color3f)
            .Set(pxr::GfVec3f(0.5f));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));

        auto material1 = usdMaterialReadCache.getCachedReadPrimMaterial(geo);
        auto material2 = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(material1->getName() == "/material");
        REQUIRE(material2->getName() == "/material");
        REQUIRE(material1 == material2);
    }

    SECTION("assigned UsdPreviewSurface with no authored attributes should fallback to spec default") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(material->getName() == "/material");
        const UsdPreviewSurface specsDefaults("spec");
        const auto usdPreviewSurface = getAsUsdPreviewSurface(material);
        REQUIRE(usdPreviewSurface->diffuseColor == specsDefaults.diffuseColor);
        REQUIRE(usdPreviewSurface->emissiveColor == specsDefaults.emissiveColor);
        REQUIRE(usdPreviewSurface->useSpecularWorkflow == specsDefaults.useSpecularWorkflow);
        REQUIRE(usdPreviewSurface->specularColor == specsDefaults.specularColor);
        REQUIRE(usdPreviewSurface->metallic == specsDefaults.metallic);
        REQUIRE(usdPreviewSurface->roughness == specsDefaults.roughness);
        REQUIRE(usdPreviewSurface->clearcoat == specsDefaults.clearcoat);
        REQUIRE(usdPreviewSurface->clearcoatRoughness == specsDefaults.clearcoatRoughness);
        REQUIRE(usdPreviewSurface->opacity == specsDefaults.opacity);
        REQUIRE(usdPreviewSurface->opacityThreshold == specsDefaults.opacityThreshold);
        REQUIRE(usdPreviewSurface->ior == specsDefaults.ior);
    }

    SECTION("assigned UsdPreviewSurface with a connection in diffuseColor should fallback to default value") {
        auto usdUvTexture = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/material/UsdUVTexture"));
        auto rgbOutput = usdUvTexture.CreateOutput(pxr::TfToken("rgb"), pxr::SdfValueTypeNames->Float3);
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));
        usdShadeShader.CreateInput(pxr::TfToken("diffuseColor"), pxr::SdfValueTypeNames->Color3f)
            .ConnectToSource(rgbOutput);

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(material->getName() == "/material");
        REQUIRE(getAsUsdPreviewSurface(material)->diffuseColor == Color(0.18f, 0.18f, 0.18f));
    }
}

}