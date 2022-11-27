#include <catch2/catch.hpp>
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

TEST_CASE("UsdUtils::getAttributeValueAs") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto sphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/sphere"));
    sphere.GetRadiusAttr().Set(3.0);

    SECTION("should read attribute value") {
        auto radius = UsdUtils::getStaticAttributeValueAs<double>(sphere.GetRadiusAttr());

        REQUIRE(radius == 3.0);
    }

    SECTION("should throw exception when there is an error reading the attribute") {
        REQUIRE_THROWS_AS(UsdUtils::getStaticAttributeValueAs<float>(sphere.GetRadiusAttr()), std::runtime_error);
    }

}

}