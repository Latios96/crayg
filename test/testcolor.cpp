#include <Color.h>
#include <catch.hpp>



TEST_CASE("createColorDefault", "[Color]"){
    Color myColor;
    REQUIRE(myColor.r == 0);
    REQUIRE(myColor.g == 0);
    REQUIRE(myColor.b == 0);
}

TEST_CASE("createColor", "[Color]"){
    Color myColor(1,2,3);
    REQUIRE(myColor.r == 1);
    REQUIRE(myColor.g == 2);
    REQUIRE(myColor.b == 3);
}

TEST_CASE("operatorAdd", "[Color]"){
    Color myColor(1,2,3);
    Color otherColor(4,5,6);

    Color result = myColor + otherColor;

    REQUIRE(result.r == 5);
    REQUIRE(result.g == 7);
    REQUIRE(result.b == 9);
}

TEST_CASE("operatorSubstract", "[Color]"){
    Color myColor(1,2,3);
    Color otherColor(4,5,6);

    Color result = myColor - otherColor;

    REQUIRE(result.r == -3);
    REQUIRE(result.g == -3);
    REQUIRE(result.b == -3);
}

TEST_CASE("operatorMultiplyColor", "[Color]"){
    Color myColor(1,2,3);
    Color otherColor(4,5,6);

    Color result = myColor * otherColor;

    REQUIRE(result.r == 4);
    REQUIRE(result.g == 10);
    REQUIRE(result.b == 18);
}

TEST_CASE("operatorMultiplyScalar", "[Color]"){
    Color myColor(1,2,3);

    Color result = myColor * 2;

    REQUIRE(result.r == 2);
    REQUIRE(result.g == 4);
    REQUIRE(result.b == 6);
}

TEST_CASE("clamp", "[Color]"){
    Color myColor(2,3,4);

    Color result = myColor.clamp();

    REQUIRE(result.r == 1);
    REQUIRE(result.g == 1);
    REQUIRE(result.b == 1);
}

TEST_CASE("getRgbValuesClamped", "[Color]"){
    Color myColor(2,3,4);

    std::tuple<int, int, int> values = myColor.getRgbValues();

    REQUIRE(std::get<0>(values) == 255);
    REQUIRE(std::get<1>(values) == 255);
    REQUIRE(std::get<2>(values) == 255);
}

TEST_CASE("getRgbValues", "[Color]"){
    Color myColor(0.1f,0.2f, 0.3f);

    std::tuple<int, int, int> values = myColor.getRgbValues();

    REQUIRE(std::get<0>(values) == 25);
    REQUIRE(std::get<1>(values) == 51);
    REQUIRE(std::get<2>(values) == 76);
}

TEST_CASE("equalOperator", "[Color]"){
    Color myColor(0.1f,0.2f, 0.3f);
    Color myOtherColor(0.1f,0.2f, 0.3f);
    Color myOtherOtherColor(0.4f,0.5f, 0.6f);

    REQUIRE(myColor == myOtherColor);
    REQUIRE_FALSE(myColor == myOtherOtherColor);
}

TEST_CASE("notEqualOperator", "[Color]"){
    Color myColor(0.1f,0.2f, 0.3f);
    Color myOtherColor(0.1f,0.2f, 0.3f);
    Color myOtherOtherColor(0.4f,0.5f, 0.6f);

    REQUIRE_FALSE(myColor != myOtherColor);
    REQUIRE(myColor != myOtherOtherColor);
}
