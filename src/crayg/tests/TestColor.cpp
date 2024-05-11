#include <basics/Color.h>
#include <catch2/catch.hpp>

namespace crayg {

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

TEST_CASE("Color/createColor from float*", "[Color]") {
    float data[3] = {1, 2, 3};

    Color myColor(data);

    REQUIRE(myColor.r == 1);
    REQUIRE(myColor.g == 2);
    REQUIRE(myColor.b == 3);
}

TEST_CASE("Color/fromRGB", "[Color]") {
    const Color color = Color::fromRGB(10, 20, 30);
    REQUIRE(color == Color(0.039215688f, 0.078431375f, 0.11764706f));
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

TEST_CASE("Color/operatorDivideColor", "[Color]") {
    Color myColor(1, 2, 3);
    Color otherColor(4, 5, 6);

    Color result = myColor / otherColor;

    REQUIRE(result.r == 0.25f);
    REQUIRE(result.g == (2.f / 5.f));
    REQUIRE(result.b == 0.5f);
}

TEST_CASE("Color/operatorMultiplyScalar", "[Color]") {
    Color myColor(1, 2, 3);

    Color result = myColor * 2;

    REQUIRE(result.r == 2);
    REQUIRE(result.g == 4);
    REQUIRE(result.b == 6);
}

TEST_CASE("Color/clamp", "[Color]") {

    SECTION("clamp to white") {
        Color myColor(2, 3, 4);

        Color result = myColor.clamp();

        REQUIRE(result == Color::createWhite());
    }

    SECTION("clamp to black") {
        Color myColor(-2, -3, -4);

        Color result = myColor.clamp();

        REQUIRE(result == Color::createBlack());
    }

    SECTION("clamp NaN to white") {
        Color myColor(NAN, NAN, NAN);

        Color result = myColor.clamp();

        REQUIRE(result == Color::createBlack());
    }
}

TEST_CASE("Color/getRgbValues", "[Color]") {
    auto testData = GENERATE(table<Color, std::tuple<int, int, int>>({{{0.1f, 0.2f, 0.3f}, {25, 51, 76}},
                                                                      {{-0.1f, 0.2f, 0.3f}, {0, 51, 76}},
                                                                      {{1.1f, 0.2f, 0.3f}, {255, 51, 76}},
                                                                      {{NAN, NAN, NAN}, {0, 0, 0}}}));
    auto colorToConvert = std::get<0>(testData);
    auto expectedTuple = std::get<1>(testData);

    std::tuple<int, int, int> values = colorToConvert.getRgbValues();

    REQUIRE(values == expectedTuple);
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

TEST_CASE("Color/divide", "[Color]") {
    Color color(1, 2, 3);
    const Color dividedColor = color / 2;
    REQUIRE(dividedColor == Color(0.5, 1, 1.5));
}

TEST_CASE("Color/isBlack", "[Color]") {
    SECTION("isBlack should return true") {
        Color color = Color::createBlack();

        REQUIRE(color.isBlack());
    }

    SECTION("isBlack should return false") {
        Color color = Color::createWhite();

        REQUIRE_FALSE(color.isBlack());
    }
}

TEST_CASE("Color/pow", "[Color]") {
    const Color color(1, 2, 3);

    const Color result = color.pow(2);

    REQUIRE(result == Color(1, 4, 9));
}

TEST_CASE("Color::operator+=", "[Color]") {
    Color color(1, 2, 3);

    color += Color(4, 5, 6);

    REQUIRE(color == Color(5, 7, 9));
}

TEST_CASE("Color::operator-=", "[Color]") {
    Color color(1, 2, 3);

    color -= Color(4, 5, 6);

    REQUIRE(color == Color(-3, -3, -3));
}

TEST_CASE("Color::operator*=", "[Color]") {
    Color color(1, 2, 3);

    color *= Color(4, 5, 6);

    REQUIRE(color == Color(4, 10, 18));
}

TEST_CASE("Color::operator/=", "[Color]") {
    Color color(1, 2, 3);

    color /= Color(2, 2, 2);

    REQUIRE(color == Color(0.5, 1, 1.5));
}

TEST_CASE("Color::operator+= scalar", "[Color]") {
    Color color(1, 2, 3);

    color += 4;

    REQUIRE(color == Color(5, 6, 7));
}

TEST_CASE("Color::operator-= scalar", "[Color]") {
    Color color(1, 2, 3);

    color -= 4;

    REQUIRE(color == Color(-3, -2, -1));
}

TEST_CASE("Color::operator*= scalar", "[Color]") {
    Color color(1, 2, 3);

    color *= 4;

    REQUIRE(color == Color(4, 8, 12));
}

TEST_CASE("Color::operator/= scalar", "[Color]") {
    Color color(1, 2, 3);

    color /= 2;

    REQUIRE(color == Color(0.5, 1, 1.5));
}

TEST_CASE("Color::isNan", "[Color]") {
    SECTION("should return false for black color") {
        REQUIRE_FALSE(Color::createBlack().isNan());
    }
    SECTION("should return true if r in NaN") {
        REQUIRE(Color(std::nan(""), 2.f, 3.f).isNan());
    }
    SECTION("should return true if g in NaN") {
        REQUIRE(Color(1.f, std::nan(""), 3).isNan());
    }
    SECTION("should return true if b in NaN") {
        REQUIRE(Color(1.f, 2.f, std::nan("")).isNan());
    }
}

}
