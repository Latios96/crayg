#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdSphereWriter.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include <pxr/usd/usd/stage.h>
#include "scene/primitives/Sphere.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

TEST_CASE("UsdSphereWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory);

    SECTION("should write sphere") {
        auto sphere = std::make_shared<Sphere>(Vector3f(1, 2, 3), 3.0f);

        UsdSphereWriter usdSphereWriter(sphere, usdMaterialWriteCache);
        usdSphereWriter.write(stage, usdPathFactory);

        auto usdGeomSphere = pxr::UsdGeomSphere(stage->GetPrimAtPath(pxr::SdfPath("/Sphere0")));
        auto radius = UsdUtils::getStaticAttributeValueAs<double>(usdGeomSphere.GetRadiusAttr());
        REQUIRE(radius == 3);
        const pxr::GfVec3d
            translation = usdGeomSphere.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation();
        REQUIRE(translation == pxr::GfVec3f(1, 2, -3));
    }
}

}