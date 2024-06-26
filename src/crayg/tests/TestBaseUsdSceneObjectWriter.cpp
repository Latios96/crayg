#include "scene/primitives/Sphere.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/base/BaseUsdSceneObjectWriter.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

static std::string getMaterialPath(const pxr::UsdPrim &spherePrim) {
    pxr::UsdShadeMaterialBindingAPI bindingApi(spherePrim);
    auto material = bindingApi.ComputeBoundMaterial();
    return material.GetPath().GetString();
}

TEST_CASE("BaseUsdSceneObjectWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory, usdShadingNodeWriteCache);

    Sphere sphere(Vector3f(1, 2, 3), 3.0f);

    class DummyBaseWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomSphere, Sphere> {
      public:
        DummyBaseWriter(Sphere &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache)
            : BaseUsdSceneObjectWriter(craygObject, usdMaterialWriteCache) {
        }
    };

    DummyBaseWriter dummyBaseWriter(sphere, usdMaterialWriteCache);

    SECTION("should write material") {
        auto diffuseMaterial = std::make_shared<UsdPreviewSurface>("myMat", Color::createGrey(0.5f));
        sphere.setMaterial(diffuseMaterial);

        dummyBaseWriter.write(stage, usdPathFactory);

        auto spherePrim = stage->GetPrimAtPath(pxr::SdfPath("/Sphere0"));
        REQUIRE(getMaterialPath(spherePrim) == "/myMat");
    }

    SECTION("object without material should be written without errors") {
        dummyBaseWriter.write(stage, usdPathFactory);

        auto spherePrim = stage->GetPrimAtPath(pxr::SdfPath("/Sphere0"));
        REQUIRE(getMaterialPath(spherePrim) == "");
    }
}

}