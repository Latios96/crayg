#include <catch2/catch.hpp>
#include "scene/Light.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/BaseUsdLightWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usdLux/sphereLight.h>

namespace crayg {

TEST_CASE("BaseUsdLightWriter::write") {

    class DummyBaseWriter : public BaseUsdLightWriter<pxr::UsdLuxSphereLight, Light> {
     public:
        DummyBaseWriter(const std::shared_ptr<Light> &craygObject) : BaseUsdLightWriter<pxr::UsdLuxSphereLight,
                                                                                        Light>(craygObject) {}
     protected:
        std::string getTranslatedType() override {
            return "test";
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write object translation to prim") {
        auto light = std::make_shared<Light>(Transform::withPosition({1, 2, -3}), 3.0f);
        light->setName("light");
        light->setColor({1, 0, 0});

        DummyBaseWriter dummyBaseWriter(light);
        dummyBaseWriter.write(stage, usdPathFactory);
        auto usdLuxSphereLight = pxr::UsdLuxSphereLight(stage->GetPrimAtPath(pxr::SdfPath("/light")));

        auto intensity = UsdUtils::getAttributeValueAs<float>(usdLuxSphereLight.GetIntensityAttr());
        REQUIRE(intensity == 3);
        auto color = UsdUtils::getAttributeValueAs<pxr::GfVec3f>(usdLuxSphereLight.GetColorAttr());
        REQUIRE(color == pxr::GfVec3f(1, 0, 0));
    }
}

}