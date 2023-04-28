#include <basics/Vector3f.h>
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("Vector3f::operator+") {
    Vector3f myVector(1, 1, 1);
    Vector3f otherVector(1, 2, 3);

    Vector3f result = myVector + otherVector;

    REQUIRE(result.x == 2);
    REQUIRE(result.y == 3);
    REQUIRE(result.z == 4);
}

TEST_CASE("Vector3f::operator-") {
    Vector3f myVector(1, 1, 1);
    Vector3f otherVector(1, 2, 3);

    Vector3f result = myVector - otherVector;

    REQUIRE(result.x == 0);
    REQUIRE(result.y == -1);
    REQUIRE(result.z == -2);
}

TEST_CASE("Vector3f::length") {
    Vector3f myVector(-5, -6, -8);

    REQUIRE(myVector.length() == Catch::Detail::Approx(11.18033f));
}

TEST_CASE("Vector3f::lengthSquared") {
    Vector3f myVector(-5, -6, -8);

    REQUIRE(myVector.lengthSquared() == Catch::Detail::Approx(125));
}

TEST_CASE("Vector3f::operator+ scalar") {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector + 5;

    REQUIRE(result.x == 10);
    REQUIRE(result.y == 11);
    REQUIRE(result.z == 13);
}

TEST_CASE("Vector3f::operator*") {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector * 5;

    REQUIRE(result.x == 25);
    REQUIRE(result.y == 30);
    REQUIRE(result.z == 40);
}

TEST_CASE("Vector3f::operator/") {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector / 5;

    REQUIRE(result.x == 1);
    REQUIRE(result.y == 6.f / 5.f);
    REQUIRE(result.z == 8.f / 5.f);
}

TEST_CASE("Vector3f::operator+=") {
    Vector3f myVector(1, 2, 3);
    myVector += Vector3f(4, 5, 6);

    REQUIRE(myVector == Vector3f(5, 7, 9));
}

TEST_CASE("Vector3f::operator-=") {
    Vector3f myVector(1, 2, 3);
    myVector -= Vector3f(4, 5, 6);

    REQUIRE(myVector == Vector3f(-3, -3, -3));
}

TEST_CASE("Vector3f::operator+= scalar") {
    Vector3f myVector(1, 2, 3);
    myVector += 1;

    REQUIRE(myVector == Vector3f(2, 3, 4));
}

TEST_CASE("Vector3f::operator-= scalar") {
    Vector3f myVector(1, 2, 3);
    myVector -= 1;

    REQUIRE(myVector == Vector3f(0, 1, 2));
}

TEST_CASE("Vector3f::operator*= scalar") {
    Vector3f myVector(1, 2, 3);
    myVector *= 2;

    REQUIRE(myVector == Vector3f(2, 4, 6));
}

TEST_CASE("Vector3f::operator/= scalar") {
    Vector3f myVector(1, 2, 3);
    myVector /= 2;

    REQUIRE(myVector == Vector3f(0.5, 1, 1.5));
}

TEST_CASE("Vector3f::normalize") {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector.normalize();

    REQUIRE(result.x == Catch::Detail::Approx(0.44721f));
    REQUIRE(result.y == Catch::Detail::Approx(0.53666f));
    REQUIRE(result.z == Catch::Detail::Approx(0.71554f));
}

TEST_CASE("Vector3f::invert") {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector.invert();

    REQUIRE(result.x == myVector.x * -1);
    REQUIRE(result.y == myVector.y * -1);
    REQUIRE(result.z == myVector.z * -1);
}

TEST_CASE("Vector3f::cross") {
    Vector3f myVector(1, 2, 3);
    Vector3f otherVector(1, 5, 7);
    Vector3f result = myVector.cross(otherVector);

    REQUIRE(result.x == -1);
    REQUIRE(result.y == -4);
    REQUIRE(result.z == 3);
}

TEST_CASE("Vector3f::operatorEqual") {
    Vector3f myVector(1, 2, 3);
    Vector3f otherVector(1, 2, 3);
    Vector3f anotherVector(0, 0, 0);

    REQUIRE(myVector == otherVector);
    REQUIRE_FALSE(myVector == anotherVector);
}

TEST_CASE("Vector3f::operatorNotEqual") {
    Vector3f myVector(1, 2, 3);
    Vector3f otherVector(1, 2, 3);
    Vector3f anotherVector(0, 0, 0);

    REQUIRE_FALSE(myVector != otherVector);
    REQUIRE(myVector != anotherVector);
}

TEST_CASE("Vector3f::shouldCreateInvalid") {
    Vector3f invalid = Vector3f::createInvalid();
    REQUIRE(invalid.x == std::numeric_limits<float>::max());
    REQUIRE(invalid.y == std::numeric_limits<float>::max());
    REQUIRE(invalid.z == std::numeric_limits<float>::max());
}

TEST_CASE("Vector3f::shouldBeInvalid") {
    Vector3f invalid = Vector3f::createInvalid();
    REQUIRE_FALSE(invalid.isValid());
}

TEST_CASE("Vector3f::reflect") {

    SECTION("should reflect vector correctly") {
        const Vector3f vectorToReflect = Vector3f(0, -1, 1);

        const Vector3f result = vectorToReflect.reflect({0, 1, 0});

        REQUIRE(result == Vector3f(0, 1, 1));
    }

    SECTION("should exactly at normal correctly") {
        const Vector3f vectorToReflect = Vector3f(0, -1, 0);

        const Vector3f result = vectorToReflect.reflect({0, 1, 0});

        REQUIRE(result == Vector3f(0, 1, 0));
    }
}

TEST_CASE("Vector3f::to Vector2f conversion") {

    const Vector3f myVector(1, 2, 3);

    SECTION("should convert xy components to Vector2f") {
        REQUIRE(myVector.xy() == Vector2f(1, 2));
    }

    SECTION("should convert xz components to Vector2f") {
        REQUIRE(myVector.xz() == Vector2f(1, 3));
    }

    SECTION("should convert yz components to Vector2f") {
        REQUIRE(myVector.yz() == Vector2f(2, 3));
    }
}

}