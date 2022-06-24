#include <catch2/catch.hpp>
#include "scene/RectLight.h"
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
        auto sphere = std::make_shared<RectLight>(Transform::withPosition({1, 2, -3}), 3.0f, 4.0f, 5.0f);
        sphere->setName("light");

        UsdRectLightWriter usdRectLightWriter(sphere);
        usdRectLightWriter.write(stage, usdPathFactory);
        auto usdLuxRectLight = pxr::UsdLuxRectLight(stage->GetPrimAtPath(pxr::SdfPath("/light")));

        auto intensity = UsdUtils::getAttributeValueAs<float>(usdLuxRectLight.GetIntensityAttr());
        auto width = UsdUtils::getAttributeValueAs<float>(usdLuxRectLight.GetWidthAttr());
        auto height = UsdUtils::getAttributeValueAs<float>(usdLuxRectLight.GetHeightAttr());
        REQUIRE(intensity == 3);
        REQUIRE(width == 4);
        REQUIRE(height == 5);
    }
}

}