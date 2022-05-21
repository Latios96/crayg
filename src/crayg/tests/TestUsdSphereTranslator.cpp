//
// Created by Jan on 21.05.2022.
//
#include <catch2/catch.hpp>
#include "sceneIO/read/usd/UsdSphereTranslator.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("UsdSphereTranslator::translate") {

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should translate sphere") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));
        pxr::UsdGeomXformCommonAPI(usdSphere).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdSphere.GetRadiusAttr().Set(3.0);

        UsdSphereTranslator usdSphereTranslator(usdSphere);
        auto sphere = usdSphereTranslator.translate();

        REQUIRE(sphere->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(sphere->getRadius() == 3);
    }
}

}