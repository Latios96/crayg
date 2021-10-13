//
// Created by Jan Honsbrok on 02.01.20.
//

#include <scene/PointCloud.h>
#include <catch2/catch.hpp>
#include <fakeit.hpp>
using namespace fakeit;

namespace crayg {

TEST_CASE("PointCloud") {

    SECTION("serialize") {
        std::vector<Vector3f> points = {{1, 2, 3}, {4, 5, 6}};
        std::vector<float> radii = {0.1f, 0.2f};
        PointCloud myPointCloud;
        myPointCloud.setPoints(points);
        myPointCloud.setRadii(radii);

        fakeit::Mock<Serializer> mockSerializer;
        fakeit::When(Method(mockSerializer, writeVector3fArray)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeVector3f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeFloatArray)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();

        Serializer &s = mockSerializer.get();
        myPointCloud.serialize(s);

        fakeit::Verify(Method(mockSerializer, writeVector3fArray)).Once();
        fakeit::Verify(Method(mockSerializer, writeVector3fArray)).Once();
        fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform", Matrix4x4f()));
        fakeit::Verify(Method(mockSerializer, writeType).Using("PointCloud"));
    }

    SECTION("deserialize") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(true);
        When(Method(mockDeserializer, readVector3fArray)).AlwaysReturn();
        When(Method(mockDeserializer, readFloatArray)).AlwaysReturn();
        When(Method(mockDeserializer, readVector3f).Using("position")).Return(Vector3f(1, 2, 3));

        Deserializer &s = mockDeserializer.get();
        PointCloud myPointCloud;

        myPointCloud.deserialize(s);

        REQUIRE(myPointCloud.getPosition() == Vector3f(1, 2, 3));
    }
}

TEST_CASE("PointCloudGetBounds") {
    std::vector<Vector3f> points = {{1, 2, 3}, {4, 5, 6}};
    std::vector<float> radii = {0.1f, 0.2f};
    PointCloud myPointCloud;
    myPointCloud.setPoints(points);
    myPointCloud.setRadii(radii);

    const BoundingBox bounds = myPointCloud.getBounds();

    REQUIRE(bounds == BoundingBox({0.9f, 1.9f, 2.9f},
                                  {4.2f, 5.2f, 6.2f}));
}

}

