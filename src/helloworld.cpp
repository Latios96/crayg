#include<iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

class Vector3f {
public:
	float x, y, z;
	
	/**
	Creates a new Vector and initialised x,y,z to 0
	*/
	Vector3f() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3f(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	// TODO use operator overloading
	Vector3f add(const Vector3f &otherVector) {
		return Vector3f(x + otherVector.x, y + otherVector.y, z + otherVector.z);
	}

	Vector3f substract(const Vector3f &otherVector) {
		return Vector3f(x - otherVector.x, y - otherVector.y, z - otherVector.z);
	}

	Vector3f multiplyScalar(float scalar) {
		return Vector3f(x*scalar, y*scalar, z*scalar);
	}

	float length() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	Vector3f normalize() {
		float length = this->length();
		// TODO optimize with computing 1/length and multiply with vector components
		return Vector3f(x / length, y / length, z / length);
	}

	Vector3f invert() {
		return Vector3f(x*-1, y*-1, z*-1);
	}

	Vector3f crossProduct(const Vector3f &otherVector) {
		return Vector3f(y * otherVector.z - otherVector.y * z,
			z * otherVector.x - otherVector.z * x,
			x * otherVector.y - otherVector.x * y);
	}
	
};

bool compareWithPrecision(float A, float B, float epsilon = 0.001f)
{
	return (fabs(A - B) < epsilon);
}

TEST_CASE("Vector3f Addition") {
	Vector3f myVector(1,1,1);
	Vector3f otherVector(1,2,3);
	Vector3f result = myVector.add(otherVector);

	REQUIRE(result.x == 2);
	REQUIRE(result.y == 3);
	REQUIRE(result.z == 4);
}

TEST_CASE("Vector3f Subtraction") {
	Vector3f myVector(1, 1, 1);
	Vector3f otherVector(1, 2, 3);
	Vector3f result = myVector.substract(otherVector);

	REQUIRE(result.x == 0);
	REQUIRE(result.y == -1);
	REQUIRE(result.z == -2);
}

TEST_CASE("Vector3f length") {
	Vector3f myVector(-5, -6, -8);
	REQUIRE(compareWithPrecision(myVector.length(), 11.18033f));
}

TEST_CASE("Vector3f multiplyScalar") {
	Vector3f myVector(5, 6, 8);
	Vector3f result = myVector.multiplyScalar(5);
	REQUIRE(result.x == 25);
	REQUIRE(result.y == 30);
	REQUIRE(result.z == 40);
}

TEST_CASE("Vector3f normalize") {
	Vector3f myVector(5, 6, 8);
	Vector3f result = myVector.normalize();
	REQUIRE(compareWithPrecision(result.x, 0.44721f));
	REQUIRE(compareWithPrecision(result.y, 0.5366f));
	REQUIRE(compareWithPrecision(result.z, 0.71554f));
}

TEST_CASE("Vector3f invert") {
	Vector3f myVector(5, 6, 8);
	Vector3f result = myVector.invert();
	REQUIRE(result.x == myVector.x*-1);
	REQUIRE(result.y == myVector.y*-1);
	REQUIRE(result.z == myVector.z*-1);
}

TEST_CASE("Vector3f crossProduct") {
	Vector3f myVector(1,2,3);
	Vector3f otherVector(1, 5, 7);
	Vector3f result = myVector.crossProduct(otherVector);

	REQUIRE(result.x == -1);
	REQUIRE(result.y == -4);
	REQUIRE(result.z == 3);
}

int main(int argc, char* argv[]) {
	// global setup...

	int result = Catch::Session().run(argc, argv);

	// global clean-up...
	system("PAUSE");
	return result;
}