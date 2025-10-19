#include "scene/io/usd/UsdUtils.h"
#include "scene/io/write/usd/UsdPathFactory.h"
#include "scene/io/write/usd/lights/UsdPointLightWriter.h"
#include "scene/lights/Light.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usdLux/sphereLight.h>

namespace crayg {

TEST_CASE("UsdPointLightWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write object translation to prim") {
        Light light(Transform::withPosition({1, 2, -3}), 3.f);
        light.setName("light");

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