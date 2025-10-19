#include "scene/io/read/usd/base/BaseUsdLightReader.h"
#include "scene/lights/DiskLight.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

TEST_CASE("BaseUsdLightReader::read") {

    class DummyBaseReader : public BaseUsdLightReader<pxr::UsdLuxDiskLight, DiskLight> {
      public:
        DummyBaseReader(const pxr::UsdLuxDiskLight &usdPrim) : BaseUsdLightReader(usdPrim) {
        }

      protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should read diskLight to DiskLight") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));
        pxr::UsdGeomXformCommonAPI(usdDiskLight).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdDiskLight.GetIntensityAttr().Set(3.0f);
        usdDiskLight.GetColorAttr().Set(pxr::GfVec3f(1, 0, 0));
        usdDiskLight.GetRadiusAttr().Set(3.0f);

        DummyBaseReader baseUsdLightReader(usdDiskLight);
        auto light = baseUsdLightReader.read();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
        REQUIRE(light->getColor() == Color({1, 0, 0}));
        REQUIRE(light->getName() == "/usdDiskLight");
    }

    SECTION("should read diskLight with time samples correctly") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));
        pxr::UsdGeomXformCommonAPI(usdDiskLight).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdDiskLight.GetIntensityAttr().Set(3.0f, pxr::UsdTimeCode());
        usdDiskLight.GetColorAttr().Set(pxr::GfVec3f(1, 0, 0), pxr::UsdTimeCode());
        usdDiskLight.GetRadiusAttr().Set(3.0f, pxr::UsdTimeCode());

        DummyBaseReader baseUsdLightReader(usdDiskLight);
        auto light = baseUsdLightReader.read();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
        REQUIRE(light->getColor() == Color({1, 0, 0}));
        REQUIRE(light->getName() == "/usdDiskLight");
    }
}

}