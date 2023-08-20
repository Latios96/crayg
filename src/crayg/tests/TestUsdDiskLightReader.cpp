#include "sceneIO/read/usd/lights/UsdDiskLightReader.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

TEST_CASE("UsdDiskLightReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should read diskLight to DiskLight") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));
        pxr::UsdGeomXformCommonAPI(usdDiskLight).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdDiskLight.GetIntensityAttr().Set(3.0f);
        usdDiskLight.GetColorAttr().Set(pxr::GfVec3f(1, 0, 0));
        usdDiskLight.GetRadiusAttr().Set(3.0f);

        UsdDiskLightReader usdDiskLightReader(usdDiskLight);
        auto light = usdDiskLightReader.read();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
        REQUIRE(light->getColor() == Color({1, 0, 0}));
        REQUIRE(light->getRadius() == 3);
    }

    SECTION("should read diskLight with time samples correctly") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));
        pxr::UsdGeomXformCommonAPI(usdDiskLight).SetTranslate(pxr::GfVec3f(1, 2, 3), pxr::UsdTimeCode());
        usdDiskLight.GetIntensityAttr().Set(3.0f, pxr::UsdTimeCode());
        usdDiskLight.GetColorAttr().Set(pxr::GfVec3f(1, 0, 0), pxr::UsdTimeCode());
        usdDiskLight.GetRadiusAttr().Set(3.0f, pxr::UsdTimeCode());

        UsdDiskLightReader usdDiskLightReader(usdDiskLight);
        auto light = usdDiskLightReader.read();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
        REQUIRE(light->getColor() == Color({1, 0, 0}));
        REQUIRE(light->getRadius() == 3);
    }
}

}