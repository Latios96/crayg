#include <catch2/catch.hpp>
#include "sceneIO/read/usd/BaseUsdXformableReader.h"
#include "scene/primitives/Sphere.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("BaseUsdXformableReader::read") {

    class DummyBaseReader : public BaseUsdXformableReader<pxr::UsdGeomSphere, Sphere> {
     public:
        DummyBaseReader(const pxr::UsdGeomSphere &usdPrim) : BaseUsdXformableReader(usdPrim) {}
     protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should read prim translation") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));
        pxr::UsdGeomXformCommonAPI(usdSphere).SetTranslate(pxr::GfVec3f(1, 2, 3));

        DummyBaseReader dummyBaseReader(usdSphere);
        auto sphere = dummyBaseReader.read();

        REQUIRE(sphere->getTransform().toPosition() == Vector3f(1, 2, -3));
    }

    SECTION("should read time sampled prim translation correctly") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));
        pxr::UsdGeomXformCommonAPI(usdSphere).SetTranslate(pxr::GfVec3f(1, 2, 3), pxr::UsdTimeCode());

        DummyBaseReader dummyBaseReader(usdSphere);
        auto sphere = dummyBaseReader.read();

        REQUIRE(sphere->getTransform().toPosition() == Vector3f(1, 2, -3));
    }
}

}