#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdSphereWriter.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include <pxr/usd/usd/stage.h>
#include "scene/primitives/Sphere.h"
#include "sceneIO/usd/UsdUtils.h"
#include "scene/lights/DiskLight.h"
#include "sceneIO/write/usd/UsdDiskLightWriter.h"

namespace crayg {

TEST_CASE("UsdDiskLightWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write disk light") {
        auto diskLight = std::make_shared<DiskLight>(Transform::withPosition({1, 2, -3}), 3, 4);
        diskLight->setColor({1, 0, 0});

        UsdDiskLightWriter usdDiskLightWriter(diskLight);
        usdDiskLightWriter.write(stage, usdPathFactory);

        auto usdLuxDiskLight = pxr::UsdLuxDiskLight(stage->GetPrimAtPath(pxr::SdfPath("/DiskLight0")));
        auto radius = UsdUtils::getStaticAttributeValueAs<float>(usdLuxDiskLight.GetRadiusAttr());
        auto intensity = UsdUtils::getStaticAttributeValueAs<float>(usdLuxDiskLight.GetIntensityAttr());
        auto color = UsdUtils::getStaticAttributeValueAs<pxr::GfVec3f>(usdLuxDiskLight.GetColorAttr());
        REQUIRE(intensity == 3);
        REQUIRE(color == pxr::GfVec3f(1, 0, 0));
        REQUIRE(radius == 4);
    }
}

}