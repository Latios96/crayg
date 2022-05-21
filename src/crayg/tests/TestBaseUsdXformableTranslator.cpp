//
// Created by Jan on 21.05.2022.
//
#include <catch2/catch.hpp>
#include "sceneIO/read/usd/BaseUsdXformableTranslator.h"
#include "scene/Sphere.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("BaseUsdXformableTranslator::translate") {

    class DummyBaseTranslator : public BaseUsdXformableTranslator<pxr::UsdGeomSphere, Sphere> {
     public:
        DummyBaseTranslator(const pxr::UsdGeomSphere &usdPrim) : BaseUsdXformableTranslator(usdPrim) {}
     protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should translate prim translation") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));
        pxr::UsdGeomXformCommonAPI(usdSphere).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdSphere.GetRadiusAttr().Set(3.0);

        DummyBaseTranslator dummyBaseTranslator(usdSphere);
        auto sphere = dummyBaseTranslator.translate();

        REQUIRE(sphere->getTransform().toPosition() == Vector3f(1, 2, -3));
    }
}

}