#include <Vector3f.h>
#include <catch.hpp>

bool compareWithPrecision(float A, float B, float epsilon = 0.001f)
{
    return (fabs(A - B) < epsilon);
}

TEST_CASE( "addTwoVectors", "[Vector]" ) {
    Vector3f myVector(1,1,1);
    Vector3f otherVector(1,2,3);

    Vector3f result = myVector.add(otherVector);

    REQUIRE(result.x == 2);
    REQUIRE(result.y == 3);
    REQUIRE(result.z == 4);
}

TEST_CASE( "addTwoVectorsOperator", "[Vector]" ) {
    Vector3f myVector(1,1,1);
    Vector3f otherVector(1,2,3);

    Vector3f result = myVector + otherVector;

    REQUIRE(result.x == 2);
    REQUIRE(result.y == 3);
    REQUIRE(result.z == 4);
}

TEST_CASE( "subtractTwoVectors", "[Vector]" ) {
    Vector3f myVector(1,1,1);
    Vector3f otherVector(1,2,3);

    Vector3f result = myVector.substract(otherVector);

    REQUIRE(result.x == 0);
    REQUIRE(result.y == -1);
    REQUIRE(result.z == -2);
}

TEST_CASE( "subtractTwoVectorsOperator", "[Vector]" ) {
    Vector3f myVector(1,1,1);
    Vector3f otherVector(1,2,3);

    Vector3f result = myVector - otherVector;

    REQUIRE(result.x == 0);
    REQUIRE(result.y == -1);
    REQUIRE(result.z == -2);
}

TEST_CASE( "length", "[Vector]" ) {
    Vector3f myVector(-5, -6, -8);

    REQUIRE(compareWithPrecision(myVector.length(), 11.18033f));
}

TEST_CASE( "multiplyScalar", "[Vector]" ) {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector.multiplyScalar(5);

    REQUIRE(result.x == 25);
    REQUIRE(result.y == 30);
    REQUIRE(result.z == 40);
}

TEST_CASE( "multiplyScalarOperator", "[Vector]" ) {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector * 5;

    REQUIRE(result.x == 25);
    REQUIRE(result.y == 30);
    REQUIRE(result.z == 40);
}

TEST_CASE( "normalize", "[Vector]" ) {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector.normalize();

    REQUIRE(compareWithPrecision(result.x, 0.44721f));
    REQUIRE(compareWithPrecision(result.y, 0.5366f));
    REQUIRE(compareWithPrecision(result.z, 0.71554f));
}

TEST_CASE( "invert", "[Vector]" ) {
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector.invert();

    REQUIRE(result.x == myVector.x*-1);
    REQUIRE(result.y == myVector.y*-1);
    REQUIRE(result.z == myVector.z*-1);
}

TEST_CASE( "crossProduct", "[Vector]" ) {
    Vector3f myVector(1,2,3);
    Vector3f otherVector(1, 5, 7);
    Vector3f result = myVector.crossProduct(otherVector);

    REQUIRE(result.x == -1);
    REQUIRE(result.y == -4);
    REQUIRE(result.z ==  3);
}

TEST_CASE( "crossProductOperator", "[Vector]" ) {
    Vector3f myVector(1,2,3);
    Vector3f otherVector(1, 5, 7);
    Vector3f result = myVector * otherVector;

    REQUIRE(result.x == -1);
    REQUIRE(result.y == -4);
    REQUIRE(result.z == 3);
}

TEST_CASE( "operatorEqual", "[Vector]" ) {
    Vector3f myVector(1,2,3);
    Vector3f otherVector(1, 2, 3);
    Vector3f anotherVector(0, 0, 0);

    REQUIRE(myVector == otherVector);
    REQUIRE_FALSE(myVector == anotherVector);
}

TEST_CASE( "operatorNotEqual", "[Vector]" ) {
    Vector3f myVector(1,2,3);
    Vector3f otherVector(1, 2, 3);
    Vector3f anotherVector(0, 0, 0);

    REQUIRE_FALSE(myVector != otherVector);
    REQUIRE(myVector != anotherVector);
}