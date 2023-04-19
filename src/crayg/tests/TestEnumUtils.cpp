#include "utils/EnumUtils.h"
#include <catch2/catch.hpp>

namespace crayg {

enum MyTestEnum { VALUE_1, VALUE_2 };

TEST_CASE("EnumUtils::parseOrThrow(string)") {

    SECTION("should parse value successfully") {
        auto value = EnumUtils::parseOrThrow<MyTestEnum>("VALUE_1");

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should parse value case insensitive") {
        auto value = EnumUtils::parseOrThrow<MyTestEnum>("value_1");

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        REQUIRE_THROWS_AS(EnumUtils::parseOrThrow<MyTestEnum>("VALUE_!"), std::runtime_error);
    }
}

TEST_CASE("EnumUtils::parseOrThrow(int)") {

    SECTION("should parse value successfully") {
        auto value = EnumUtils::parseOrThrow<MyTestEnum>(0);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        REQUIRE_THROWS_AS(EnumUtils::parseOrThrow<MyTestEnum>(4), std::runtime_error);
    }
}

TEST_CASE("EnumUtils::parseOrDefault(string)") {

    SECTION("should parse value successfully") {
        auto value = EnumUtils::parseOrDefault<MyTestEnum>("VALUE_1", MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should parse value case insensitive") {
        auto value = EnumUtils::parseOrDefault<MyTestEnum>("value_1", MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        auto value = EnumUtils::parseOrDefault<MyTestEnum>("VALUE_!", MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_2);
    }
}

TEST_CASE("EnumUtils::parseOrDefault(int)") {

    SECTION("should parse value successfully") {
        auto value = EnumUtils::parseOrDefault<MyTestEnum>(0, MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        auto value = EnumUtils::parseOrDefault<MyTestEnum>(4, MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_2);
    }
}

}