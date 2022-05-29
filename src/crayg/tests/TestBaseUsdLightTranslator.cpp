//
// Created by Jan on 21.05.2022.
//
#include <catch2/catch.hpp>
#include "sceneIO/read/usd/BaseUsdLightTranslator.h"
#include "scene/DiskLight.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdLux/diskLight.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("BaseUsdLightTranslator::translator") {

    class DummyBaseTranslator : public BaseUsdLightTranslator<pxr::UsdLuxDiskLight, DiskLight> {
     public:
        DummyBaseTranslator(const pxr::UsdLuxDiskLight &usdPrim) : BaseUsdLightTranslator(usdPrim) {}
     protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should translate diskLight to DiskLight") {
        auto usdDiskLight = pxr::UsdLuxDiskLight::Define(stage, pxr::SdfPath("/usdDiskLight"));
        pxr::UsdGeomXformCommonAPI(usdDiskLight).SetTranslate(pxr::GfVec3f(1, 2, 3));
        usdDiskLight.GetIntensityAttr().Set(3.0f);
        usdDiskLight.GetRadiusAttr().Set(3.0f);

        DummyBaseTranslator baseUsdLightTranslator(usdDiskLight);
        auto light = baseUsdLightTranslator.translate();

        REQUIRE(light->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(light->getIntensity() == 3);
    }

}

}