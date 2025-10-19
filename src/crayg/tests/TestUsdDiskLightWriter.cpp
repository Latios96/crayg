#include "scene/io/usd/UsdUtils.h"
#include "scene/io/write/usd/UsdPathFactory.h"
#include "scene/io/write/usd/lights/UsdDiskLightWriter.h"
#include "scene/io/write/usd/primitives/UsdSphereWriter.h"
#include "scene/lights/DiskLight.h"
#include "scene/primitives/Sphere.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>

namespace crayg {

TEST_CASE("UsdDiskLightWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write disk light") {
        DiskLight diskLight(Transform::withPosition({1, 2, -3}), 3.f, 4.f);
        diskLight.setColor({1, 0, 0});

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