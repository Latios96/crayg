//
// Created by Jan on 21.05.2022.
//
#include <catch2/catch.hpp>
#include "sceneIO/read/usd/BaseUsdReader.h"
#include "scene/Sphere.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

TEST_CASE("BaseUsdReader::read") {

    class DummyBaseReader : public BaseUsdReader<pxr::UsdGeomSphere, Sphere> {
     public:
        DummyBaseReader(const pxr::UsdGeomSphere &usdPrim) : BaseUsdReader(usdPrim) {}
     protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should read prim") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));

        DummyBaseReader dummyBaseReader(usdSphere);
        auto sphere = dummyBaseReader.read();

        REQUIRE(sphere != nullptr);
    }
}

}