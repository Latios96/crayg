#include <scene/Sphere.h>
#include <catch2/catch.hpp>
#include <fakeit.hpp>
using namespace fakeit;

namespace crayg {

TEST_CASE("Sphere") {
    auto mySphere = std::make_shared<Sphere>(Vector3f(0, 0, 0), 3.0f);

    SECTION("createSphere") {
        // make sure radius is correctly set
        REQUIRE(mySphere->getRadius() == 3.0f);
    }

    SECTION("isIntersecting") {
        // tests intersecting ray
        Ray intersectingRay(Vector3f(1, 0, 0), Vector3f(-1, 0, 0));
        // intersects should return true
        REQUIRE(mySphere->isIntersecting(intersectingRay));

        // tests not intersecting ray
        Ray notIntersectingRay(Vector3f(0, 0, 5), Vector3f(-1, 0, 0));
        // intersects should return true
        REQUIRE_FALSE(mySphere->isIntersecting(notIntersectingRay));
    }

    SECTION("intersect_") {
        auto mySphere = std::make_shared<Sphere>(Vector3f(1, 0, 0), 3.0f);
        Ray ray(Vector3f(5, 0, 0), Vector3f(-1, 0, 0));

        float t = mySphere->intersect(ray).rayParameter;
        Vector3f hitLocation = ray.constructIntersectionPoint(t);

        REQUIRE(hitLocation.x == Catch::Detail::Approx(4));
        REQUIRE(hitLocation.y == Catch::Detail::Approx(0));
        REQUIRE(hitLocation.z == Catch::Detail::Approx(0));
    }

    SECTION("intersectNotReturnsMax") {
        auto hitRay = mySphere->intersect(Ray(Vector3f(1, 10, -5), Vector3f(0, 0, 1)));
        REQUIRE(hitRay.rayParameter == std::numeric_limits<float>::max());
    }

    SECTION("serialize") {
        fakeit::Mock<Serializer> mockSerializer;
        fakeit::When(Method(mockSerializer, writeFloat)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeVector3f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeString)).AlwaysReturn();

        Serializer &s = mockSerializer.get();
        mySphere->serialize(s);

        fakeit::Verify(Method(mockSerializer, writeFloat).Using("radius", 3.0f));
        fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform", Matrix4x4f()));
        fakeit::Verify(Method(mockSerializer, writeType).Using("Sphere"));
        fakeit::Verify(Method(mockSerializer, writeString)).Never();
    }

    SECTION("deserialize") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(true);
        When(Method(mockDeserializer, readFloat).Using("radius")).Return(3.0f);
        When(Method(mockDeserializer, readVector3f).Using("position")).Return(Vector3f(1, 2, 3));

        Deserializer &s = mockDeserializer.get();
        mySphere->deserialize(s);

        REQUIRE(mySphere->getPosition() == Vector3f(1, 2, 3));
        REQUIRE(mySphere->getRadius() == 3.0f);
    }
}

TEST_CASE("Sphere/transformation") {
    auto mySphere = std::make_shared<Sphere>(Vector3f(1, 2, 3), 3.0f);

    REQUIRE(mySphere->getPosition() == Vector3f(1, 2, 3));
}

TEST_CASE("Sphere/intersectsTransformed") {
    auto mySphere = std::make_shared<Sphere>(Vector3f(1, 2, 3), 1.0f);

    REQUIRE(mySphere->isIntersecting(Ray(Vector3f(1, 2, 6), Vector3f(0, 0, -1))));
}

}

