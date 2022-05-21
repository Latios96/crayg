//
// Created by Jan on 21.05.2022.
//
#include <catch2/catch.hpp>
#include "sceneIO/read/usd/BaseUsdTranslator.h"
#include "scene/Sphere.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

TEST_CASE("BaseUsdTranslator::translate") {

    class DummyBaseTranslator : public BaseUsdTranslator<pxr::UsdGeomSphere, Sphere> {
     public:
        DummyBaseTranslator(const pxr::UsdGeomSphere &usdPrim) : BaseUsdTranslator(usdPrim) {}
     protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should translate prim") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));

        DummyBaseTranslator dummyBaseTranslator(usdSphere);
        auto sphere = dummyBaseTranslator.translate();

        REQUIRE(sphere != nullptr);
    }
}

}