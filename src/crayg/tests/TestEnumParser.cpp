#include "utils/EnumParser.h"
#include <catch2/catch.hpp>

namespace crayg {

enum class MyTestEnum { VALUE_1, VALUE_2 };

TEST_CASE("EnumParser::parse(string)") {

    SECTION("should parse value successfully") {
        auto value = EnumParser::parse<MyTestEnum>("VALUE_1");

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should parse value case insensitive") {
        auto value = EnumParser::parse<MyTestEnum>("value_1");

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should return empty enum if value does not exist") {
        auto value = EnumParser::parse<MyTestEnum>("value_!t ru");

        REQUIRE(value == std::nullopt);
    }
}

TEST_CASE("EnumParser::parse(int)") {

    SECTION("should parse value successfully") {
        auto value = EnumParser::parse<MyTestEnum>(0);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        auto value = EnumParser::parse<MyTestEnum>(4);

        REQUIRE(value == std::nullopt);
    }
}

TEST_CASE("EnumParser::parseOrThrow(string)") {

    SECTION("should parse value successfully") {
        auto value = EnumParser::parseOrThrow<MyTestEnum>("VALUE_1");

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should parse value case insensitive") {
        auto value = EnumParser::parseOrThrow<MyTestEnum>("value_1");

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        REQUIRE_THROWS_AS(EnumParser::parseOrThrow<MyTestEnum>("VALUE_!"), std::runtime_error);
    }
}

TEST_CASE("EnumParser::parseOrThrow(int)") {

    SECTION("should parse value successfully") {
        auto value = EnumParser::parseOrThrow<MyTestEnum>(0);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        REQUIRE_THROWS_AS(EnumParser::parseOrThrow<MyTestEnum>(4), std::runtime_error);
    }
}

TEST_CASE("EnumParser::parseOrDefault(string)") {

    SECTION("should parse value successfully") {
        auto value = EnumParser::parseOrDefault<MyTestEnum>("VALUE_1", MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should parse value case insensitive") {
        auto value = EnumParser::parseOrDefault<MyTestEnum>("value_1", MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        auto value = EnumParser::parseOrDefault<MyTestEnum>("VALUE_!", MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_2);
    }
}

TEST_CASE("EnumParser::parseOrDefault(int)") {

    SECTION("should parse value successfully") {
        auto value = EnumParser::parseOrDefault<MyTestEnum>(0, MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_1);
    }

    SECTION("should throw if value does not exist") {
        auto value = EnumParser::parseOrDefault<MyTestEnum>(4, MyTestEnum::VALUE_2);

        REQUIRE(value == MyTestEnum::VALUE_2);
    }
}

}