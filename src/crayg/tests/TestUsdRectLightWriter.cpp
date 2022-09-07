#include <catch2/catch.hpp>
#include "scene/lights/RectLight.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/BaseUsdLightWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/UsdRectLightWriter.h"
#include <pxr/usd/usdLux/rectLight.h>

namespace crayg {

TEST_CASE("UsdRectLightWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write rect light") {
        auto light = std::make_shared<RectLight>(Transform::withPosition({1, 2, -3}), 3.0f, 4.0f, 5.0f);
        light->setName("light");
        light->setColor({1, 0, 0});

        UsdRectLightWriter usdRectLightWriter(light);
        usdRectLightWriter.write(stage, usdPathFactory);
        auto usdLuxRectLight = pxr::UsdLuxRectLight(stage->GetPrimAtPath(pxr::SdfPath("/light")));

        auto intensity = UsdUtils::getAttributeValueAs<float>(usdLuxRectLight.GetIntensityAttr());
        auto color = UsdUtils::getAttributeValueAs<pxr::GfVec3f>(usdLuxRectLight.GetColorAttr());
        auto width = UsdUtils::getAttributeValueAs<float>(usdLuxRectLight.GetWidthAttr());
        auto height = UsdUtils::getAttributeValueAs<float>(usdLuxRectLight.GetHeightAttr());
        REQUIRE(intensity == 3);
        REQUIRE(color == pxr::GfVec3f(1, 0, 0));
        REQUIRE(width == 4);
        REQUIRE(height == 5);
    }
}

}