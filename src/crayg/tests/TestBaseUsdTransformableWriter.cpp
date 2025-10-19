#include "scene/io/usd/UsdUtils.h"
#include "scene/io/write/usd/UsdPathFactory.h"
#include "scene/io/write/usd/base/BaseUsdTransformableWriter.h"
#include "scene/primitives/Sphere.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

TEST_CASE("BaseUsdTransformableWriter::write") {

    class DummyBaseWriter : public BaseUsdTransformableWriter<pxr::UsdGeomSphere, Sphere> {
      public:
        DummyBaseWriter(Sphere &craygObject) : BaseUsdTransformableWriter<pxr::UsdGeomSphere, Sphere>(craygObject) {
        }

      protected:
        std::string getTranslatedType() override {
            return std::string("test");
        }
    };

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;

    SECTION("should write object translation to prim") {
        Sphere sphere(Vector3f(1, 2, -3), 3.0f);
        sphere.setName("craygSphere");

        DummyBaseWriter dummyBaseWriter(sphere);
        dummyBaseWriter.write(stage, usdPathFactory);
        auto usdGeomSphere = pxr::UsdGeomSphere(stage->GetPrimAtPath(pxr::SdfPath("/craygSphere")));

        pxr::GfVec3d translation =
            usdGeomSphere.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation();
        REQUIRE(translation == pxr::GfVec3f(1, 2, 3));
    }
}

}