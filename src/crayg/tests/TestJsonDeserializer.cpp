//
// Created by jan on 29.12.18.
//
#include <catch2/catch.hpp>
#include <sceneIO/read/json/JsonDeserializer.h>

namespace crayg {

TEST_CASE("JsonDeserializer") {
    const char json[] = R"({"myFloat": 1.0,
"myInt": 2,
"mvVector3f": [1,2,3],
"myVector3fArray": [[1,2,3],[4,5,6]],
"myIntArray": [1,2,3],
"myFloatArray": [0.1,0.2,0.3],
"myMatrix4x4f": [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1],
"myMatrix4x4fInvalid": [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0],
"myString": "testString",
"myColor": [1,2,3]
})";
    rapidjson::StringStream s(json);
    rapidjson::Document d;
    d.ParseStream(s);
    JsonDeserializer jsonDeserializer(d);

    SECTION("hasPropertyShouldReturnTrue") {
        REQUIRE(jsonDeserializer.hasProperty("myFloat"));
    }

    SECTION("hasPropertyShouldReturnFalse") {
        REQUIRE_FALSE(jsonDeserializer.hasProperty("dtr"));
    }

    SECTION("readFloatShouldReturn1.0") {
        REQUIRE(jsonDeserializer.readFloat("myFloat") == 1.0);
    }

    SECTION("readFloatShouldThrowException") {
        REQUIRE_THROWS_AS(jsonDeserializer.readFloat("myNotExistingFloat"), std::invalid_argument);
    }

    SECTION("readIntShouldReturn2") {
        REQUIRE(jsonDeserializer.readInt("myInt") == 2);
    }

    SECTION("readIntShouldThrowException") {
        REQUIRE_THROWS_AS(jsonDeserializer.readInt("myNotExistingInt"), std::invalid_argument);
    }

    SECTION("readVector3fShouldReturn{1,2,3}") {
        REQUIRE(jsonDeserializer.readVector3f("mvVector3f") == Vector3f(1, 2, 3));
    }

    SECTION("readVectorShouldThrowException") {
        REQUIRE_THROWS_AS(jsonDeserializer.readVector3f("mvVectoeer3f"), std::invalid_argument);
    }

    SECTION("readVector3fArrayShouldReturn[{1,2,3},{4,5,6}") {
        std::vector<Vector3f> vector3fArray;
        jsonDeserializer.readVector3fArray("myVector3fArray", vector3fArray);
        REQUIRE(vector3fArray.size() == 2);
        REQUIRE(vector3fArray[0] == Vector3f(1, 2, 3));
        REQUIRE(vector3fArray[1] == Vector3f(4, 5, 6));
    }

    SECTION("readVector3fArrayShouldThrowException") {
        std::vector<Vector3f> vector3fArray;
        REQUIRE_THROWS_AS(jsonDeserializer.readVector3fArray("mvVectoeer3f", vector3fArray), std::invalid_argument);
    }

    SECTION("readIntArrayShouldReturn{1,2,3}") {
        std::vector<int> intArray;
        jsonDeserializer.readIntArray("myIntArray", intArray);
        REQUIRE(intArray.size() == 3);
        REQUIRE(intArray[0] == 1);
        REQUIRE(intArray[1] == 2);
        REQUIRE(intArray[2] == 3);
    }

    SECTION("readIntArrayShouldThrowException") {
        std::vector<int> intArray;
        REQUIRE_THROWS_AS(jsonDeserializer.readIntArray("e", intArray), std::invalid_argument);
    }

    SECTION("readFloatArrayShouldReturn{0.1,0.2,0.3}") {
        std::vector<float> floatArray;
        jsonDeserializer.readFloatArray("myFloatArray", floatArray);
        REQUIRE(floatArray.size() == 3);
        REQUIRE(floatArray[0] == 0.1f);
        REQUIRE(floatArray[1] == 0.2f);
        REQUIRE(floatArray[2] == 0.3f);
    }

    SECTION("readFloatArrayShouldThrowException") {
        std::vector<float> floatArray;
        REQUIRE_THROWS_AS(jsonDeserializer.readFloatArray("e", floatArray), std::invalid_argument);
    }

    SECTION("readMatrix4x4fShouldReturnCorrect") {
        const Matrix4x4f expectedMatrix;
        const Matrix4x4f matrix = jsonDeserializer.readMatrix4x4f("myMatrix4x4f");

        REQUIRE(matrix == expectedMatrix);
    }

    SECTION("readFloatArrayShouldThrowExceptionWrongArraySize") {
        REQUIRE_THROWS_AS(jsonDeserializer.readMatrix4x4f("myMatrix4x4fInvalid"), std::invalid_argument);
    }

    SECTION("readFloatArrayShouldThrowExceptionNotFound") {
        REQUIRE_THROWS_AS(jsonDeserializer.readMatrix4x4f("e"), std::invalid_argument);
    }

    SECTION("readStringShouldThrowException") {
        REQUIRE_THROWS_AS(jsonDeserializer.readString("e"), std::invalid_argument);
    }

    SECTION("readStringShouldReadCorrectly") {
        REQUIRE(jsonDeserializer.readString("myString") == "testString");
    }

    SECTION("readColorShouldThrowException") {
        REQUIRE_THROWS_AS(jsonDeserializer.readColor("e"), std::invalid_argument);
    }

    SECTION("readColorShouldReadCorrectly") {
        REQUIRE(jsonDeserializer.readColor("myColor") == Color(1, 2, 3));
    }

    SECTION("readIntWithDefaultShouldReturnDefault") {
        REQUIRE(jsonDeserializer.readIntWithDefault("notExistingNameToReadDefault", 2) == 2);
    }

    SECTION("readFloatWithDefaultShouldReturnDefault") {
        REQUIRE(jsonDeserializer.readFloatWithDefault("notExistingNameToReadDefault", 3.3f) == 3.3f);
    }

    SECTION("readColorWithDefaultShouldReturnDefault") {
        REQUIRE(jsonDeserializer.readColorWithDefault("notExistingNameToReadDefault", Color::createWhite())
                    == Color::createWhite());
    }

    SECTION("readVector3fWithDefaultShouldReturnDefault") {
        REQUIRE(
            jsonDeserializer.readVector3fWithDefault("notExistingNameToReadDefault", {1, 2, 3}) == Vector3f(1, 2, 3));
    }

    SECTION("readStringWithDefaultShouldReturnDefault") {
        REQUIRE(jsonDeserializer.readStringWithDefault("notExistingNameToReadDefault", "testStr") == "testStr");
    }

    SECTION("readMatrixWithDefaultShouldReturnDefault") {
        REQUIRE(
            jsonDeserializer.readMatrix4x4fWithDefault("notExistingNameToReadDefault", Matrix4x4f()) == Matrix4x4f());
    }
}

}

