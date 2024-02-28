#include "sceneIO/read/usd/primitives/UsdPointInstancerReader.h"
#include "sceneIO/read/usd/shadingnetworks/caches/UsdMaterialReadCache.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

struct PointInstancerTransformFixture {
    pxr::UsdGeomPointInstancer usdGeomPointInstancer;
    pxr::UsdGeomSphere proto;
};

PointInstancerTransformFixture setupPointInstancerTransformFixture(pxr::UsdStagePtr stage) {
    auto proto = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/sphere"));
    auto usdGeomPointInstancer = pxr::UsdGeomPointInstancer::Define(stage, pxr::SdfPath("/usdGeomPointInstancer"));
    pxr::VtInt64Array ids({0});
    usdGeomPointInstancer.GetIdsAttr().Set(ids);
    pxr::VtIntArray protoIndices({0});
    usdGeomPointInstancer.GetProtoIndicesAttr().Set(protoIndices);
    usdGeomPointInstancer.GetPrototypesRel().AddTarget(pxr::SdfPath("/protos/sphere"));
    pxr::UsdGeomXformCommonAPI(usdGeomPointInstancer).SetTranslate(pxr::GfVec3f(1, 2, 3));
    return {usdGeomPointInstancer, proto};
}

TEST_CASE("UsdPointInstancerReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdMaterialReadCache usdMaterialTranslationCache;

    SECTION("should read single prototype with single Imageable") {
        auto proto = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/sphere"));
        auto usdGeomPointInstancer = pxr::UsdGeomPointInstancer::Define(stage, pxr::SdfPath("/usdGeomPointInstancer"));
        pxr::VtInt64Array ids({0, 1, 2});
        usdGeomPointInstancer.GetIdsAttr().Set(ids);
        pxr::VtIntArray protoIndices({0, 0, 0});
        usdGeomPointInstancer.GetProtoIndicesAttr().Set(protoIndices);
        usdGeomPointInstancer.GetPrototypesRel().AddTarget(pxr::SdfPath("/protos/sphere"));

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->ids == std::vector<size_t>({0, 1, 2}));
        REQUIRE(pointInstancer->protoIndices == std::vector<size_t>({0, 0, 0}));
        REQUIRE(pointInstancer->protos.size() == 1);
        REQUIRE(pointInstancer->protos[0]->name == "/protos/sphere");
        REQUIRE(pointInstancer->protos[0]->members.size() == 1);
        REQUIRE(pointInstancer->protos[0]->members[0]->getType() == "Sphere");
    }

    SECTION("should read single prototype with multiple Imageables") {
        auto proto1 = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto/proto1"));
        auto proto2 = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto/proto2"));
        auto usdGeomPointInstancer = pxr::UsdGeomPointInstancer::Define(stage, pxr::SdfPath("/usdGeomPointInstancer"));
        pxr::VtInt64Array ids({0, 1, 2});
        usdGeomPointInstancer.GetIdsAttr().Set(ids);
        pxr::VtIntArray protoIndices({0, 0, 0});
        usdGeomPointInstancer.GetProtoIndicesAttr().Set(protoIndices);
        usdGeomPointInstancer.GetPrototypesRel().AddTarget(pxr::SdfPath("/protos/myProto"));

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->ids == std::vector<size_t>({0, 1, 2}));
        REQUIRE(pointInstancer->protoIndices == std::vector<size_t>({0, 0, 0}));
        REQUIRE(pointInstancer->protos.size() == 1);
        REQUIRE(pointInstancer->protos[0]->members.size() == 2);
        REQUIRE(pointInstancer->protos[0]->name == "/protos/myProto");
        REQUIRE(pointInstancer->protos[0]->members[0]->getType() == "Sphere");
        REQUIRE(pointInstancer->protos[0]->members[1]->getType() == "Sphere");
    }

    SECTION("should read multiple prototypes with single Imageable") {
        auto proto1 = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto/proto1"));
        auto proto2 = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto/proto2"));
        auto usdGeomPointInstancer = pxr::UsdGeomPointInstancer::Define(stage, pxr::SdfPath("/usdGeomPointInstancer"));
        pxr::VtInt64Array ids({0, 1, 2, 3});
        usdGeomPointInstancer.GetIdsAttr().Set(ids);
        pxr::VtIntArray protoIndices({0, 1, 0, 1});
        usdGeomPointInstancer.GetProtoIndicesAttr().Set(protoIndices);
        usdGeomPointInstancer.GetPrototypesRel().SetTargets(
            {pxr::SdfPath("/protos/myProto/proto1"), pxr::SdfPath("/protos/myProto/proto2")});

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->ids == std::vector<size_t>({0, 1, 2, 3}));
        REQUIRE(pointInstancer->protoIndices == std::vector<size_t>({0, 1, 0, 1}));
        REQUIRE(pointInstancer->protos.size() == 2);
        REQUIRE(pointInstancer->protos[0]->members.size() == 1);
        REQUIRE(pointInstancer->protos[0]->name == "/protos/myProto/proto1");
        REQUIRE(pointInstancer->protos[0]->members[0]->getType() == "Sphere");
        REQUIRE(pointInstancer->protos[1]->members.size() == 1);
        REQUIRE(pointInstancer->protos[1]->name == "/protos/myProto/proto2");
        REQUIRE(pointInstancer->protos[1]->members[0]->getType() == "Sphere");
    }

    SECTION("should read multiple prototypes with multiple Imageables") {
        pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto1/sphere1"));
        pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto1/sphere2"));
        pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto2/sphere1"));
        pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto2/sphere2"));
        auto usdGeomPointInstancer = pxr::UsdGeomPointInstancer::Define(stage, pxr::SdfPath("/usdGeomPointInstancer"));
        pxr::VtInt64Array ids({0, 1, 2, 3});
        usdGeomPointInstancer.GetIdsAttr().Set(ids);
        pxr::VtIntArray protoIndices({0, 1, 0, 1});
        usdGeomPointInstancer.GetProtoIndicesAttr().Set(protoIndices);
        usdGeomPointInstancer.GetPrototypesRel().SetTargets(
            {pxr::SdfPath("/protos/myProto1"), pxr::SdfPath("/protos/myProto2")});

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->ids == std::vector<size_t>({0, 1, 2, 3}));
        REQUIRE(pointInstancer->protoIndices == std::vector<size_t>({0, 1, 0, 1}));
        REQUIRE(pointInstancer->protos.size() == 2);
        REQUIRE(pointInstancer->protos[0]->members.size() == 2);
        REQUIRE(pointInstancer->protos[0]->name == "/protos/myProto1");
        REQUIRE(pointInstancer->protos[0]->members[0]->getType() == "Sphere");
        REQUIRE(pointInstancer->protos[0]->members[1]->getType() == "Sphere");
        REQUIRE(pointInstancer->protos[1]->members.size() == 2);
        REQUIRE(pointInstancer->protos[1]->name == "/protos/myProto2");
        REQUIRE(pointInstancer->protos[1]->members[0]->getType() == "Sphere");
        REQUIRE(pointInstancer->protos[1]->members[1]->getType() == "Sphere");
    }

    SECTION("should read transform correctly [transform on PointInstancer, no transform authored for protos]") {
        auto [usdGeomPointInstancer, proto] = setupPointInstancerTransformFixture(stage);

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->getTransform() == Transform::withPosition({1, 2, -3}));
        REQUIRE(pointInstancer->transforms == std::vector<Transform>(1));
    }

    SECTION("should read transform correctly [transform on PointInstancer, transform authored for protos]") {
        auto [usdGeomPointInstancer, proto] = setupPointInstancerTransformFixture(stage);
        pxr::VtVec3fArray positions({{1, 2, 3}});
        usdGeomPointInstancer.GetPositionsAttr().Set(positions);

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->getTransform() == Transform::withPosition({1, 2, -3}));
        REQUIRE(pointInstancer->transforms == std::vector<Transform>({Transform::withPosition({1, 2, -3})}));
    }

    SECTION("should read transform correctly [transform on PointInstancer, transform authored on protos]") {
        auto [usdGeomPointInstancer, proto] = setupPointInstancerTransformFixture(stage);
        pxr::VtVec3fArray positions({{0, 0, 0}});
        usdGeomPointInstancer.GetPositionsAttr().Set(positions);
        pxr::UsdGeomXformCommonAPI(proto).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->getTransform() == Transform::withPosition({1, 2, -3}));
        REQUIRE(pointInstancer->transforms == std::vector<Transform>({Transform::withPosition({1, 2, -3})}));
    }

    SECTION("should read transform correctly [transform on PointInstancer, transform authored for and on protos]") {
        auto [usdGeomPointInstancer, proto] = setupPointInstancerTransformFixture(stage);
        pxr::VtVec3fArray positions({{1, 2, 3}});
        usdGeomPointInstancer.GetPositionsAttr().Set(positions);
        pxr::UsdGeomXformCommonAPI(proto).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->getTransform() == Transform::withPosition({1, 2, -3}));
        REQUIRE(pointInstancer->transforms == std::vector<Transform>({Transform::withPosition({2, 4, -6})}));
    }

    SECTION("should ignore transforms authored 'above' protos in the hierarchy") {
        auto [usdGeomPointInstancer, proto] = setupPointInstancerTransformFixture(stage);
        auto nestedXform = pxr::UsdGeomXform::Define(stage, pxr::SdfPath("/protos"));
        pxr::UsdGeomXformCommonAPI(nestedXform).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->transforms == std::vector<Transform>(1));
    }

    SECTION("should respect transforms that occur inside a proto hierarchy") {
        auto nestedXform = pxr::UsdGeomXform::Define(stage, pxr::SdfPath("/protos/myProto/nested"));
        auto proto1 = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto/nested/proto1"));
        auto proto2 = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/protos/myProto/proto2"));
        auto usdGeomPointInstancer = pxr::UsdGeomPointInstancer::Define(stage, pxr::SdfPath("/usdGeomPointInstancer"));
        pxr::VtInt64Array ids({0});
        usdGeomPointInstancer.GetIdsAttr().Set(ids);
        pxr::VtIntArray protoIndices({0});
        usdGeomPointInstancer.GetProtoIndicesAttr().Set(protoIndices);
        usdGeomPointInstancer.GetPrototypesRel().AddTarget(pxr::SdfPath("/protos/myProto"));
        pxr::UsdGeomXformCommonAPI(nestedXform).SetTranslate(pxr::GfVec3f(1, 2, 3));

        UsdPointInstancerReader usdPointInstancerReader(usdGeomPointInstancer, usdMaterialTranslationCache);
        auto pointInstancer = usdPointInstancerReader.read();

        REQUIRE(pointInstancer->transforms == std::vector<Transform>(1));
        REQUIRE(pointInstancer->protos[0]->members[0]->getTransform() == Transform::withPosition({1, 2, -3}));
    }
}

}