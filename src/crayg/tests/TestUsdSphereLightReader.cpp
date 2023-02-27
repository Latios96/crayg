#include "sceneIO/read/usd/UsdSphereLightReader.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/usd/usdLux/sphereLight.h>

namespace crayg {

TEST_CASE("UsdSphereLightReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should read sphere light to point light") {
        auto usdSphereLight = pxr::UsdLuxSphereLight::Define(stage, pxr::SdfPath("/usdSphereLight"));
        pxr::UsdGeomXformCommonAPI(usdSphereLight).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdSphereLight.GetIntensityAttr().Set(3.0f);
        usdSphereLight.GetColorAttr().Set(pxr::GfVec3f(1, 0, 0));

        UsdSphereLightReader usdSphereLightReader(usdSphereLight);
        auto light = usdSphereLightReader.read();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
        REQUIRE(light->getColor() == Color({1, 0, 0}));
    }

    SECTION("should read sphere light with time samples correctly") {
        auto usdSphereLight = pxr::UsdLuxSphereLight::Define(stage, pxr::SdfPath("/usdSphereLight"));
        pxr::UsdGeomXformCommonAPI(usdSphereLight).SetTranslate(pxr::GfVec3f(1, 2, 3), pxr::UsdTimeCode());
        usdSphereLight.GetIntensityAttr().Set(3.0f, pxr::UsdTimeCode());
        usdSphereLight.GetColorAttr().Set(pxr::GfVec3f(1, 0, 0), pxr::UsdTimeCode());

        UsdSphereLightReader usdSphereLightReader(usdSphereLight);
        auto light = usdSphereLightReader.read();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
        REQUIRE(light->getColor() == Color({1, 0, 0}));
    }
}

}