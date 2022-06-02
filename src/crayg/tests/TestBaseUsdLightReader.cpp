//
// Created by Jan on 21.05.2022.
//
#include <catch2/catch.hpp>
#include "sceneIO/read/usd/BaseUsdLightReader.h"
#include "scene/DiskLight.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdLux/diskLight.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("BaseUsdLightReader::read") {

    class DummyBaseReader : public BaseUsdLightReader<pxr::UsdLuxDiskLight, DiskLight> {
     public:
        DummyBaseReader(const pxr::UsdLuxDiskLight &usdPrim) : BaseUsdLightReader(usdPrim) {}
     protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should read diskLight to DiskLight") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));
        pxr::UsdGeomXformCommonAPI(usdDiskLight).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdDiskLight.GetIntensityAttr().Set(3.0f);
        usdDiskLight.GetRadiusAttr().Set(3.0f);

        DummyBaseReader baseUsdLightReader(usdDiskLight);
        auto light = baseUsdLightReader.read();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
        REQUIRE(light->getName() == "/usdDiskLight");
    }

}

}