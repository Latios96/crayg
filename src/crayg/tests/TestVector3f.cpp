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

}