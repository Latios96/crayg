#include <foundation/Color.h>
#include <catch2/catch.hpp>

TEST_CASE("Color/createColorDefault", "[Color]") {
    Color myColor;
    REQUIRE(myColor.r == 0);
    REQUIRE(myColor.g == 0);
    REQUIRE(myColor.b == 0);
}

TEST_CASE("Color/createColor", "[Color]") {
    Color myColor(1, 2, 3);
    REQUIRE(myColor.r == 1);
    REQUIRE(myColor.g == 2);
    REQUIRE(myColor.b == 3);
}

TEST_CASE("Color/operatorAddColor", "[Color]") {
    Color myColor(1, 2, 3);
    Color otherColor(4, 5, 6);

    Color result = myColor + otherColor;

    REQUIRE(result.r == 5);
    REQUIRE(result.g == 7);
    REQUIRE(result.b == 9);
}
TEST_CASE("Color/operatorAddFloat", "[Color]") {
    Color myColor(1, 2, 3);

    Color result = myColor + 1;

    REQUIRE(result.r == 2.0f);
    REQUIRE(result.g == 3.0f);
    REQUIRE(result.b == 4.0f);
}

TEST_CASE("Color/operatorSubstract", "[Color]") {
    Color myColor(1, 2, 3);
    Color otherColor(4, 5, 6);

    Color result = myColor - otherColor;

    REQUIRE(result.r == -3);
    REQUIRE(result.g == -3);
    REQUIRE(result.b == -3);
}

TEST_CASE("Color/operatorMultiplyColor", "[Color]") {
    Color myColor(1, 2, 3);
    Color otherColor(4, 5, 6);

    Color result = myColor * otherColor;

    REQUIRE(result.r == 4);
    REQUIRE(result.g == 10);
    REQUIRE(result.b == 18);
}

TEST_CASE("Color/operatorMultiplyScalar", "[Color]") {
    Color myColor(1, 2, 3);

    Color result = myColor * 2;

    REQUIRE(result.r == 2);
    REQUIRE(result.g == 4);
    REQUIRE(result.b == 6);
}

TEST_CASE("Color/clamp", "[Color]") {
    Color myColor(2, 3, 4);

    Color result = myColor.clamp();

    REQUIRE(result.r == 1);
    REQUIRE(result.g == 1);
    REQUIRE(result.b == 1);
}

TEST_CASE("Color/getRgbValuesClamped", "[Color]") {
    Color myColor(2, 3, 4);

    std::tuple<int, int, int> values = myColor.getRgbValues();

    REQUIRE(std::get<0>(values) == 255);
    REQUIRE(std::get<1>(values) == 255);
    REQUIRE(std::get<2>(values) == 255);
}

TEST_CASE("Color/getRgbValues", "[Color]") {
    Color myColor(0.1f, 0.2f, 0.3f);

    std::tuple<int, int, int> values = myColor.getRgbValues();

    REQUIRE(std::get<0>(values) == 25);
    REQUIRE(std::get<1>(values) == 51);
    REQUIRE(std::get<2>(values) == 76);
}

TEST_CASE("Color/equalOperator", "[Color]") {
    Color myColor(0.1f, 0.2f, 0.3f);
    Color myOtherColor(0.1f, 0.2f, 0.3f);
    Color myOtherOtherColor(0.4f, 0.5f, 0.6f);

    REQUIRE(myColor == myOtherColor);
    REQUIRE_FALSE(myColor == myOtherOtherColor);
}

TEST_CASE("Color/notEqualOperator", "[Color]") {
    Color myColor(0.1f, 0.2f, 0.3f);
    Color myOtherColor(0.1f, 0.2f, 0.3f);
    Color myOtherOtherColor(0.4f, 0.5f, 0.6f);

    REQUIRE_FALSE(myColor != myOtherColor);
    REQUIRE(myColor != myOtherOtherColor);
}
