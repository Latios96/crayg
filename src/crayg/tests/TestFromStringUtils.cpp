#include "utils/FromStringUtils.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("FromStringUtils::parseIntOrThrow") {
    SECTION("should parse positive ints") {
        auto testData = GENERATE(table<std::string, int>({{"1", 1}, {"123", 123}}));
        const int i = FromStringUtils::parseIntOrThrow(std::get<0>(testData));

        REQUIRE(i == std::get<1>(testData));
    }

    SECTION("should parse zero") {
        const int i = FromStringUtils::parseIntOrThrow("0");

        REQUIRE(i == 0);
    }

    SECTION("should parse negative ints") {
        auto testData = GENERATE(table<std::string, int>({{"-1", -1}, {"-123", -123}}));
        const int i = FromStringUtils::parseIntOrThrow(std::get<0>(testData));

        REQUIRE(i == std::get<1>(testData));
    }

    SECTION("should not parse garbage") {
        auto garbage = GENERATE("", "serse", "-,.-%&/56");
        REQUIRE_THROWS_AS(FromStringUtils::parseIntOrThrow(garbage), std::runtime_error);
    }
}

}