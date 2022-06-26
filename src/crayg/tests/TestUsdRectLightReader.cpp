#include <catch2/catch.hpp>
#include "sceneIO/read/usd/UsdRectLightReader.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdLux/rectLight.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <iostream>

namespace crayg {

TEST_CASE("UsdRectLightReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should read rect light to RectLight") {
        auto usdRectLight = pxr::UsdLuxRectLight::Define(stage, pxr::SdfPath("/usdRectLight"));
        pxr::UsdGeomXformCommonAPI(usdRectLight).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdRectLight.GetIntensityAttr().Set(3.0f);
        usdRectLight.GetColorAttr().Set(pxr::GfVec3f(1, 0, 0));
        usdRectLight.GetWidthAttr().Set(2.0f);
        usdRectLight.GetHeightAttr().Set(3.0f);

        UsdRectLightReader usdRectLightReader(usdRectLight);
        auto light = usdRectLightReader.read();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
        REQUIRE(light->getColor() == Color({1, 0, 0}));
        REQUIRE(light->getWidth() == 2);
        REQUIRE(light->getHeight() == 3);
    }

}

}