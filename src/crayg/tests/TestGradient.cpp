#include "basics/Color.h"
#include "basics/Gradient.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("Gradient::interpolate") {

    SECTION("should interpolate correctly for gradient with two values") {
        auto testData = GENERATE(table<float, Color>(
            {{0.0f, Color::createBlack()}, {0.5f, Color::createGrey(0.5f)}, {1.0f, Color::createWhite()}}));
        const auto position = std::get<0>(testData);
        const auto expectedValue = std::get<1>(testData);
        Gradient<Color> gradient({Color::createBlack(), Color::createWhite()});

        const auto result = gradient.interpolate(position);

        REQUIRE(result == expectedValue);
    }

    SECTION("should interpolate correctly for gradient with linearly distributed values") {
        auto testData = GENERATE(table<float, Color>({{0.0f, Color::createBlack()},
                                                      {0.2f, Color::createGrey(0.2f)},
                                                      {0.4f, Color::createGrey(0.4f)},
                                                      {0.6f, Color::createGrey(0.6f)},
                                                      {0.8f, Color::createGrey(0.8f)},
                                                      {1.0f, Color::createWhite()}}));
        const auto position = std::get<0>(testData);
        const auto expectedValue = std::get<1>(testData);
        Gradient<Color> gradient({Color::createBlack(), Color::createGrey(0.2f), Color::createGrey(0.4f),
                                  Color::createGrey(0.6f), Color::createGrey(0.8f), Color::createWhite()});

        const auto result = gradient.interpolate(position);

        REQUIRE(result == expectedValue);
    }

    SECTION("should interpolate correctly for gradient with uneven distributed values") {
        auto testData = GENERATE(table<float, Color>({{0.0f, Color::createBlack()},
                                                      {0.25f, Color::createGrey(0.1f)},
                                                      {0.5f, Color::createGrey(0.2f)},
                                                      {0.75f, Color::createGrey(0.6f)},
                                                      {1.0f, Color::createWhite()}}));
        const auto position = std::get<0>(testData);
        const auto expectedValue = std::get<1>(testData);
        Gradient<Color> gradient({GradientStop(0.0f, Color::createBlack()), GradientStop(0.5f, Color::createGrey(0.2f)),
                                  GradientStop(1.0f, Color::createWhite())});

        const auto result = gradient.interpolate(position);

        REQUIRE(result == expectedValue);
    }

    SECTION("should clamp positions outside [0-1] range") {
        auto testData = GENERATE(table<float, Color>({{-0.1f, Color::createBlack()}, {1.1f, Color::createWhite()}}));
        const auto position = std::get<0>(testData);
        const auto expectedValue = std::get<1>(testData);
        Gradient<Color> gradient({Color::createBlack(), Color::createWhite()});

        const auto result = gradient.interpolate(position);

        REQUIRE(result == expectedValue);
    }
}

}