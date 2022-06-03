//
// Created by Jan on 03.06.2022.
//
#include <catch2/catch.hpp>
#include "scene/Light.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/BaseUsdLightWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/UsdPointLightWriter.h"
#include <pxr/usd/usdLux/sphereLight.h>

namespace crayg {

TEST_CASE("UsdPointLightWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write object translation to prim") {
        auto sphere = std::make_shared<Light>(Transform::withPosition({1, 2, -3}), 3);
        sphere->setName("light");

        UsdPointLightWriter usdPointLightWriter(sphere);
        usdPointLightWriter.write(stage, usdPathFactory);
        auto usdLuxSphereLight = pxr::UsdLuxSphereLight(stage->GetPrimAtPath(pxr::SdfPath("/light")));

        auto intensity = UsdUtils::getAttributeValueAs<float>(usdLuxSphereLight.GetIntensityAttr());
        REQUIRE(intensity == 3);
    }
}

}