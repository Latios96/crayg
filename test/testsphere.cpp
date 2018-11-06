#include <scene/Sphere.h>
#include <catch.hpp>
#include <fakeit.hpp>
using namespace fakeit;
#include "utils/utils.h"

TEST_CASE("Sphere") {
    Sphere mySphere(Vector3f(0, 0, 0), 3.0f);

    SECTION("createSphere") {
        // make sure radius is correctly set
        REQUIRE(mySphere.getRadius() == 3.0f);
    }

    SECTION("intersects") {
        // test intersecting ray
        Ray intersectingRay(Vector3f(1, 0, 0), Vector3f(-1, 0, 0));
        // intersects should return true
        REQUIRE(mySphere.intersects(intersectingRay));

        // test not intersecting ray
        Ray notIntersectingRay(Vector3f(0, 0, 5), Vector3f(-1, 0, 0));
        // intersects should return true
        REQUIRE_FALSE(mySphere.intersects(notIntersectingRay));
    }

    SECTION("intersect"){
        Sphere mySphere(Vector3f(1, 0, 0), 3.0f);
        auto hitRay = mySphere.intersect(Ray(Vector3f(5, 0, 0), Vector3f(-1, 0, 0)));
        Vector3f hitLocation = hitRay.startPoint + (hitRay.direction * hitRay.length);
        REQUIRE(compareWithPrecision(hitLocation.x, 4));
        REQUIRE(compareWithPrecision(hitLocation.y, 0));
        REQUIRE(compareWithPrecision(hitLocation.z, 0));
    }
    SECTION("intersectNotReturnsMax"){
        auto hitRay = mySphere.intersect(Ray(Vector3f(1, 10, -5), Vector3f(0, 0, 1)));
        REQUIRE(hitRay.startPoint == Vector3f());
        REQUIRE(hitRay.direction == Vector3f());
        REQUIRE(hitRay.length == std::numeric_limits<float>::max());
    }

    SECTION("serialize"){
        fakeit::Mock<Serializer> mockSerializer;
        fakeit::When(Method(mockSerializer,writeFloat)).AlwaysReturn();
        fakeit::When(Method(mockSerializer,writeVector3f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer,writeType)).AlwaysReturn();

        Serializer &s = mockSerializer.get();
        mySphere.serialize(s);

        fakeit::Verify(Method(mockSerializer,writeFloat).Using("radius", 3.0f));
        fakeit::Verify(Method(mockSerializer,writeVector3f).Using("position", Vector3f()));
        fakeit::Verify(Method(mockSerializer,writeType).Using("Sphere"));
    }

    SECTION("deserialize"){
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer,readFloat).Using("radius")).Return(3.0f);
        When(Method(mockDeserializer,readVector3f).Using("position")).Return(Vector3f(1,2,3));

        Deserializer &s = mockDeserializer.get();
        mySphere.deserialize(s);


        REQUIRE(mySphere.getPosition() == Vector3f(1,2,3));
        REQUIRE(mySphere.getRadius() == 3.0f);
    }
}

TEST_CASE( "Sphere/transformation") {
    Sphere mySphere(Vector3f(1,2,3),3.0f);
    
    REQUIRE(mySphere.getPosition() == Vector3f(1,2,3));
}
TEST_CASE( "Sphere/intersectsTransformed") {
    Sphere mySphere(Vector3f(1,2,3),1.0f);

    REQUIRE(mySphere.intersects(Ray(Vector3f(1,2,6), Vector3f(0,0,-1))));
}


