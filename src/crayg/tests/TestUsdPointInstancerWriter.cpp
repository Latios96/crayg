#include "scene/primitives/PointInstancer.h"
#include "scene/primitives/Sphere.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/primitives/UsdPointInstancerWriter.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <pxr/usd/usd/stage.h>

namespace crayg {

TEST_CASE("UsdPointInstancerWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory, usdShadingNodeWriteCache);

    SECTION("should write point instancer") {
        auto sphere = std::make_shared<Sphere>();
        auto proto = std::make_shared<PointInstancer::Prototype>();
        proto->name = "/Sphere0";
        proto->members.push_back(sphere);
        PointInstancer pointInstancer;
        pointInstancer.protos.push_back(proto);
        pointInstancer.ids.push_back(0);
        pointInstancer.protoIndices.push_back(0);
        pointInstancer.transforms.emplace_back(Transform::withScale(2, 2, 2) * Transform::withRotation(90, 0, 0) *
                                               Transform::withPosition({1, 2, 3}));

        UsdPointInstancerWriter usdPointInstancerWriter(pointInstancer, usdMaterialWriteCache);
        auto usdPointInstancer = usdPointInstancerWriter.write(stage, usdPathFactory);

        auto ids = UsdUtils::getStaticAttributeValueAs<pxr::VtInt64Array>(usdPointInstancer.GetIdsAttr());
        auto protoIndices =
            UsdUtils::getStaticAttributeValueAs<pxr::VtIntArray>(usdPointInstancer.GetProtoIndicesAttr());
        auto positions = UsdUtils::getStaticAttributeValueAs<pxr::VtVec3fArray>(usdPointInstancer.GetPositionsAttr());
        auto orientations =
            UsdUtils::getStaticAttributeValueAs<pxr::VtQuathArray>(usdPointInstancer.GetOrientationsAttr());
        auto scales = UsdUtils::getStaticAttributeValueAs<pxr::VtVec3fArray>(usdPointInstancer.GetScalesAttr());
        pxr::SdfPathVector protoTargets;
        usdPointInstancer.GetPrototypesRel().GetTargets(&protoTargets);
        REQUIRE(ids == pxr::VtInt64Array({0}));
        REQUIRE(protoIndices == pxr::VtIntArray({0}));
        REQUIRE(positions == pxr::VtVec3fArray({{2, -6, -3.9999998}}));
        REQUIRE(orientations == pxr::VtQuathArray({pxr::GfQuath(-0.707031, 0.707031, 0, 0)}));
        REQUIRE(scales == pxr::VtVec3fArray({{2, 2, 2}}));
        REQUIRE(protoTargets == pxr::SdfPathVector({{pxr::SdfPath("/Sphere0")}}));
        REQUIRE(stage->GetPrimAtPath(pxr::SdfPath("/Sphere0")).IsDefined());
    }
}

}