//
// Created by Jan on 28.10.2021.
//


#include <catch2/catch.hpp>
#include "sceneIO/read/usd/UsdSphereLightTranslator.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdLux/sphereLight.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <iostream>

namespace crayg {

TEST_CASE("SphereLightTranslatorTranslate") {

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should translate sphere light to point light") {
        auto usdSphereLight = pxr::UsdLuxSphereLight::Define(stage, pxr::SdfPath("/usdSphereLight"));
        pxr::UsdGeomXformCommonAPI(usdSphereLight).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdSphereLight.GetIntensityAttr().Set(3.0f);

        UsdSphereLightTranslator usdSphereLightTranslator(usdSphereLight);
        auto light = usdSphereLightTranslator.translate();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
    }

}

}