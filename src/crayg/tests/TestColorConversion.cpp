#include "image/ColorConversion.h"
#include "image/ImageAlgorithms.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ColorConversion::channelNeedsLinearToSRgbConversion") {

    SECTION("should return true for rgb") {
        REQUIRE(ColorConversion::channelNeedsLinearToSRgbConversion("rgb"));
    }

    SECTION("should return false for other channels") {
        REQUIRE_FALSE(ColorConversion::channelNeedsLinearToSRgbConversion("alpa"));
        REQUIRE_FALSE(ColorConversion::channelNeedsLinearToSRgbConversion("depth"));
    }
}

TEST_CASE("ColorConversion::linearToSRGB") {

    SECTION("should convert single pixel") {
        const Color color(1, 2, 3);

        const Color result = ColorConversion::linearToSRGB(color);

        REQUIRE(result == Color(0.99697495f, 1.350231f, 1.6094257f));
    }

    SECTION("should convert PixelBuffer") {
        const auto source = PixelBuffer::createRgbFloat({10, 20});
        const auto target = PixelBuffer::createRgbFloat({10, 20});
        ImageAlgorithms::fill(*source, {1, 2, 3});

        ColorConversion::linearToSRGB(*source, *target);

        REQUIRE(target->getValue({0, 0}) == Color(0.99697495f, 1.350231f, 1.6094257f));
    }
}

TEST_CASE("ColorConversion::sRGBToLinear") {

    SECTION("should convert single pixel") {
        const Color color(1, 2, 3);

        const Color result = ColorConversion::sRGBToLinear(color);

        REQUIRE(result == Color(1.f, 1.350231f, 1.6094257f));
    }

    SECTION("should convert PixelBuffer") {
        const auto source = PixelBuffer::createRgbFloat({10, 20});
        const auto target = PixelBuffer::createRgbFloat({10, 20});
        ImageAlgorithms::fill(*source, {1, 2, 3});

        ColorConversion::sRGBToLinear(*source, *target);

        REQUIRE(target->getValue({0, 0}) == Color(1.f, 1.350231f, 1.6094257f));
    }
}

}