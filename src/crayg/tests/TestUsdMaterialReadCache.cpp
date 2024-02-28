#include "scene/shadingnetworks/materials/Material.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include "sceneIO/read/usd/shadingnetworks/caches//UsdMaterialReadCache.h"
#include <catch2/catch.hpp>
#include <pxr/base/gf/vec3f.h>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>

namespace crayg {

bool isDefaultMaterial(const std::shared_ptr<Material> &material) {
    return material->getName() == "defaultMaterial" && material->getType() == "UsdPreviewSurface";
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

        REQUIRE(material1->getName() == "/material/shader");
        REQUIRE(material2->getName() == "/material/shader");
        REQUIRE(material1 == material2);
    }
}

}