//
// Created by Jan Honsbrok on 15.11.18.
//
#include <catch2/catch.hpp>
#include <fakeit.hpp>
using namespace fakeit;
#include <scene/TriangleMesh.h>

namespace crayg {

TEST_CASE("TriangleMesh") {
    TriangleMesh cube;
    TriangleMesh::createCube(cube);

    SECTION("intersect_") {
        Ray ray({1.1f, 1.1f, -2}, {0, 0, 1});
        const Imageable::Intersection intersection = cube.intersect(ray);
        Vector3f hitLocation = ray.constructIntersectionPoint(intersection.rayParameter);
        REQUIRE_FALSE(hitLocation.isValid());
    }

    SECTION("serialize") {
        fakeit::Mock<Serializer> mockSerializer;
        fakeit::When(Method(mockSerializer, writeIntArray)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeVector3fArray)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeVector3f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();

        Serializer &s = mockSerializer.get();
        cube.serialize(s);

        //NOTE: this doesnt work correctly on Mac OS
        //fakeit::Verify(Method(mockSerializer,writeIntArray).Using("faceIndexes", cube.faceIndexes));
        fakeit::Verify(Method(mockSerializer, writeIntArray)).Once();
        fakeit::Verify(Method(mockSerializer, writeVector3fArray)).Once();
        fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform", Matrix4x4f()));
        fakeit::Verify(Method(mockSerializer, writeType).Using("TriangleMesh"));
    }

    SECTION("deserialize") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(true);
        When(Method(mockDeserializer, readVector3fArray)).AlwaysReturn();
        When(Method(mockDeserializer, readIntArray)).AlwaysReturn();
        When(Method(mockDeserializer, readVector3f).Using("position")).Return(Vector3f(1, 2, 3));

        Deserializer &s = mockDeserializer.get();
        cube.deserialize(s);

        REQUIRE(cube.getPosition() == Vector3f(1, 2, 3));
    }
}

TEST_CASE("TriangleMeshGetBounds") {
    TriangleMesh triangleMesh;
    triangleMesh.points.emplace_back(0, 0, 0);
    triangleMesh.points.emplace_back(0, 1, 0);
    triangleMesh.points.emplace_back(1, 0, 0);
    triangleMesh.faceIndexes.push_back(0);
    triangleMesh.faceIndexes.push_back(1);
    triangleMesh.faceIndexes.push_back(2);
    triangleMesh.beforeRender();

    const BoundingBox boundingBox = triangleMesh.getBounds();

    REQUIRE(boundingBox == BoundingBox({0, 0, 0}, {1, 1, 0}));
}

}
