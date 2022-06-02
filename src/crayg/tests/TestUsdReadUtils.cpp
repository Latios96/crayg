//
// Created by Jan on 28.10.2021.
//


#include <catch2/catch.hpp>
#include "sceneIO/usd/UsdReadUtils.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("UsdReadUtils::readTransform") {

    const auto stage = pxr::UsdStage::CreateInMemory();
    auto usdCamera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/cam_grp/usdCamera"));
    Transformable transformable({0, 0, 0});

    SECTION("should correctly convert transform prim which has only local transformations") {
        pxr::UsdGeomXformCommonAPI(usdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::UsdGeomXformCommonAPI(usdCamera).SetScale(pxr::GfVec3f(1, 2, 3));

        Matrix4x4f expectedMatrix(1, 0, 0, 1,
                                  0, 2, 0, 2,
                                  0, 0, 3, -3,
                                  0, 0, 0, 1);

        UsdReadUtils::readTransform(transformable, usdCamera);

        REQUIRE(transformable.getTransform().matrix == expectedMatrix);
    }

    SECTION("should correctly convert transform prim which has transformation on its parents") {
        auto parent = pxr::UsdGeomXform::Define(stage, pxr::SdfPath("/cam_grp"));
        pxr::UsdGeomXformCommonAPI(parent).SetScale(pxr::GfVec3f(1, 2, 3));
        pxr::UsdGeomXformCommonAPI(usdCamera).SetTranslate(pxr::GfVec3f(1, 2, 3));

        Matrix4x4f expectedMatrix(1, 0, 0, 1,
                                  0, 2, 0, 4,
                                  0, 0, 3, -9,
                                  0, 0, 0, 1);

        UsdReadUtils::readTransform(transformable, usdCamera);

        REQUIRE(transformable.getTransform().matrix == expectedMatrix);
    }

}

}