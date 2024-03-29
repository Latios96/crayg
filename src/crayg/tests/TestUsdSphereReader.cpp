#include "sceneIO/read/usd/primitives/UsdSphereReader.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("UsdSphereReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdMaterialReadCache usdMaterialTranslationCache;

    SECTION("should read sphere") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));
        pxr::UsdGeomXformCommonAPI(usdSphere).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdSphere.GetRadiusAttr().Set(3.0);

        UsdSphereReader usdSphereReader(usdSphere, usdMaterialTranslationCache);
        auto sphere = usdSphereReader.read();

        REQUIRE(sphere->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(sphere->getRadius() == 3);
        REQUIRE(sphere->getMaterial()->getName() == "defaultMaterial");
    }

    SECTION("should read sphere with time samples correctly") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));
        pxr::UsdGeomXformCommonAPI(usdSphere).SetTranslate(pxr::GfVec3f(1, 2, 3), pxr::UsdTimeCode());
        usdSphere.GetRadiusAttr().Set(3.0, pxr::UsdTimeCode());

        UsdSphereReader usdSphereReader(usdSphere, usdMaterialTranslationCache);
        auto sphere = usdSphereReader.read();

        REQUIRE(sphere->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(sphere->getRadius() == 3);
        REQUIRE(sphere->getMaterial()->getName() == "defaultMaterial");
    }
}

}