#include "crayg/foundation/exceptions/Exceptions.h"
#include "scene/io/read/usd/shadingnetworks/caches/UsdMaterialReadCache.h"
#include "scene/shadingnetworks/materials/Material.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include <catch2/catch.hpp>
#include <pxr/base/gf/vec3f.h>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>

namespace crayg {

std::shared_ptr<UsdPreviewSurface> getAsUsdPreviewSurface(const std::shared_ptr<Material> &material) {
    if (material->getType() != "UsdPreviewSurface") {
        CRAYG_LOG_AND_THROW(std::runtime_error("This is not a UsdPreviewSurface."));
    }
    return std::static_pointer_cast<UsdPreviewSurface>(material);
}

TEST_CASE("UsdPreviewSurfaceReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto geo = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
    auto usdShadeMaterial = pxr::UsdShadeMaterial::Define(stage, pxr::SdfPath("/material"));
    auto usdShadeShader = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/material/shader"));

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

        REQUIRE(material->getName() == "/material/shader");
        const auto usdPreviewSurface = getAsUsdPreviewSurface(material);
        REQUIRE(usdPreviewSurface->diffuseColor.value == Color(1, 2, 3));
        REQUIRE(usdPreviewSurface->emissiveColor.value == Color(4, 5, 6));
        REQUIRE(usdPreviewSurface->useSpecularWorkflow == true);
        REQUIRE(usdPreviewSurface->specularColor.value == Color(7, 8, 9));
        REQUIRE(usdPreviewSurface->metallic.value == 0.1f);
        REQUIRE(usdPreviewSurface->roughness.value == 0.2f);
        REQUIRE(usdPreviewSurface->clearcoat.value == 0.3f);
        REQUIRE(usdPreviewSurface->clearcoatRoughness.value == 0.4f);
        REQUIRE(usdPreviewSurface->opacity.value == 0.5f);
        REQUIRE(usdPreviewSurface->opacityThreshold.value == 0.6f);
        REQUIRE(usdPreviewSurface->ior.value == 0.7f);
    }

    SECTION("assigned UsdPreviewSurface with no authored attributes should fallback to spec default") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(material->getName() == "/material/shader");
        const UsdPreviewSurface specsDefaults("spec");
        const auto usdPreviewSurface = getAsUsdPreviewSurface(material);
        REQUIRE(usdPreviewSurface->diffuseColor.value == specsDefaults.diffuseColor.value);
        REQUIRE(usdPreviewSurface->emissiveColor.value == specsDefaults.emissiveColor.value);
        REQUIRE(usdPreviewSurface->useSpecularWorkflow == specsDefaults.useSpecularWorkflow);
        REQUIRE(usdPreviewSurface->specularColor.value == specsDefaults.specularColor.value);
        REQUIRE(usdPreviewSurface->metallic.value == specsDefaults.metallic.value);
        REQUIRE(usdPreviewSurface->roughness.value == specsDefaults.roughness.value);
        REQUIRE(usdPreviewSurface->clearcoat.value == specsDefaults.clearcoat.value);
        REQUIRE(usdPreviewSurface->clearcoatRoughness.value == specsDefaults.clearcoatRoughness.value);
        REQUIRE(usdPreviewSurface->opacity.value == specsDefaults.opacity.value);
        REQUIRE(usdPreviewSurface->opacityThreshold.value == specsDefaults.opacityThreshold.value);
        REQUIRE(usdPreviewSurface->ior.value == specsDefaults.ior.value);
    }

    SECTION("assigned UsdPreviewSurface with a connection in diffuseColor should translate this connection") {
        auto colorConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/material/UsdUVTexture"));
        colorConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:ColorConstant")));
        colorConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Color3f);
        auto rgbOutput = colorConstant.CreateOutput(pxr::TfToken("rgb"), pxr::SdfValueTypeNames->Float3);
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));
        auto diffuseColor = usdShadeShader.CreateInput(pxr::TfToken("diffuseColor"), pxr::SdfValueTypeNames->Color3f);
        diffuseColor.ConnectToSource(rgbOutput);
        diffuseColor.Set(pxr::GfVec3f(0.5));

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(material->getName() == "/material/shader");
        REQUIRE(getAsUsdPreviewSurface(material)->diffuseColor.value == Color::createGrey(0.5f));
        REQUIRE(getAsUsdPreviewSurface(material)->diffuseColor.hasInputConnection());
    }

    SECTION("assigned UsdPreviewSurface with no connection, no authored value and no default value should fallback to "
            "default") {
        UsdMaterialReadCache usdMaterialReadCache;
        pxr::UsdShadeMaterialBindingAPI bindingApi(geo.GetPrim());
        bindingApi.Bind(usdShadeMaterial);
        usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));
        auto input = usdShadeShader.CreateInput(pxr::TfToken("diffuseColor"), pxr::SdfValueTypeNames->Color3f);
        REQUIRE_FALSE(input.GetAttr().HasValue());

        auto material = usdMaterialReadCache.getCachedReadPrimMaterial(geo);

        REQUIRE(material->getName() == "/material/shader");
        REQUIRE(getAsUsdPreviewSurface(material)->diffuseColor.value == Color(0.18f, 0.18f, 0.18f));
    }
}

}