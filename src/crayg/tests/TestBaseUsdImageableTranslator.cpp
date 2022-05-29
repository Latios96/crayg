//
// Created by Jan on 21.05.2022.
//
#include <catch2/catch.hpp>
#include "sceneIO/read/usd/BaseUsdImageableTranslator.h"
#include "scene/Sphere.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("BaseUsdImageableTranslator::translate") {

    class DummyBaseTranslator : public BaseUsdImageableTranslator<pxr::UsdGeomSphere, Sphere> {
     public:
        DummyBaseTranslator(const pxr::UsdGeomSphere &usdPrim, UsdMaterialTranslationCache &usdMaterialTranslationCache)
            : BaseUsdImageableTranslator(usdPrim, usdMaterialTranslationCache) {}
     protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdMaterialTranslationCache usdMaterialTranslationCache;

    SECTION("should translate materual") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));

        DummyBaseTranslator dummyBaseTranslator(usdSphere, usdMaterialTranslationCache);
        auto sphere = dummyBaseTranslator.translate();

        REQUIRE(sphere->getMaterial()->getName() == "defaultMaterial");
    }
}

}