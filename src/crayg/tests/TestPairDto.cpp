#include <catch2/catch.hpp>
#include <string>
#include <sstream>
#include "utils/PairDto.h"

namespace crayg {

CRAYG_PAIR_DTO(ExamplePairDto, int, myFirstNumber, std::string, myName)

TEST_CASE("PairDto::construct") {

    SECTION("should default construct") {
        ExamplePairDto examplePairDto;

        REQUIRE(examplePairDto.myFirstNumber == 0);
        REQUIRE(examplePairDto.myName == "");
    }

    SECTION("should construct with params") {
        ExamplePairDto examplePairDto(42, "hey");

        REQUIRE(examplePairDto.myFirstNumber == 42);
        REQUIRE(examplePairDto.myName == "hey");
    }
}

TEST_CASE("PairDto::compare") {

    SECTION("should be equal") {
        ExamplePairDto left(42, "hey");
        ExamplePairDto right(42, "hey");

        REQUIRE(left == right);
    }

    SECTION("should not be equal, different number") {
        ExamplePairDto left(41, "hey");
        ExamplePairDto right(42, "hey");

        REQUIRE(left != right);
    }

    SECTION("should not be equal, different name") {
        ExamplePairDto left(42, "hey");
        ExamplePairDto right(42, "ho");

        REQUIRE(left != right);
    }
}

TEST_CASE("PairDto::formatting") {

    SECTION("should format to ostream") {
        std::ostringstream os;
        ExamplePairDto left(42, "hey");

        os << left;

        REQUIRE(os.str() == "ExamplePairDto{myFirstNumber=42,myName=hey}");
    }

    SECTION("should format using fmt") {
        ExamplePairDto left(42, "hey");

        REQUIRE(fmt::format("{}", left) == "ExamplePairDto{myFirstNumber=42,myName=hey}");
    }
}

}