#include "crayg/scene/io/read/usd/base/BaseUsdImageableReader.h"
#include "crayg/scene/primitives/Sphere.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("BaseUsdImageableReader::read") {

    class DummyBaseReader : public BaseUsdImageableReader<pxr::UsdGeomSphere, Sphere> {
      public:
        DummyBaseReader(const pxr::UsdGeomSphere &usdPrim, UsdMaterialReadCache &usdMaterialReadCache)
            : BaseUsdImageableReader(usdPrim, usdMaterialReadCache) {
        }

      protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdMaterialReadCache usdMaterialTranslationCache;

    SECTION("should read material") {
        auto usdSphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/usdSphere"));

        DummyBaseReader dummyBaseReader(usdSphere, usdMaterialTranslationCache);
        auto sphere = dummyBaseReader.read();

        REQUIRE(sphere->getMaterial()->getName() == "defaultMaterial");
        REQUIRE(sphere->getName() == "/usdSphere");
    }
}

}