#include <catch2/catch.hpp>
#include "scene/lights/Light.h"
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
        auto light = std::make_shared<Light>(Transform::withPosition({1, 2, -3}), 3);
        light->setName("light");

        UsdPointLightWriter usdPointLightWriter(light);
        usdPointLightWriter.write(stage, usdPathFactory);
        auto usdLuxSphereLight = pxr::UsdLuxSphereLight(stage->GetPrimAtPath(pxr::SdfPath("/light")));

        auto intensity = UsdUtils::getStaticAttributeValueAs<float>(usdLuxSphereLight.GetIntensityAttr());
        auto radius = UsdUtils::getStaticAttributeValueAs<float>(usdLuxSphereLight.GetRadiusAttr());
        REQUIRE(intensity == 3);
        REQUIRE(radius == 0);
    }
}

}