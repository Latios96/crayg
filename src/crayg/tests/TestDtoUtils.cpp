#include <catch2/catch.hpp>
#include <string>
#include <sstream>
#include "utils/DtoUtils.h"
#include "Logger.h"

namespace crayg {

CRAYG_DTO_2(ExampleDto2, int, myFirstNumber, std::string, myName)
CRAYG_DTO_3(ExampleDto3, int, myFirstNumber, std::string, myName, ExampleDto2, nestedDto)

TEST_CASE("CraygDto2::construct") {

    SECTION("should default construct") {
        ExampleDto2 examplePairDto;

        REQUIRE(examplePairDto.myFirstNumber == 0);
        REQUIRE(examplePairDto.myName == "");
    }

    SECTION("should construct with params") {
        ExampleDto2 examplePairDto(42, "hey");

        REQUIRE(examplePairDto.myFirstNumber == 42);
        REQUIRE(examplePairDto.myName == "hey");
    }

    SECTION("should copy construct") {
        ExampleDto2 examplePairDto;
        ExampleDto2 other = examplePairDto;

        REQUIRE(other == examplePairDto);
    }
}

TEST_CASE("CraygDto2::compare") {

    SECTION("should be equal") {
        ExampleDto2 left(42, "hey");
        ExampleDto2 right(42, "hey");

        REQUIRE(left == right);
    }

    SECTION("should not be equal, different number") {
        ExampleDto2 left(41, "hey");
        ExampleDto2 right(42, "hey");

        REQUIRE(left != right);
    }

    SECTION("should not be equal, different name") {
        ExampleDto2 left(42, "hey");
        ExampleDto2 right(42, "ho");

        REQUIRE(left != right);
    }
}

TEST_CASE("CraygDto2::formatting") {

    SECTION("should format to ostream") {
        std::ostringstream os;
        ExampleDto2 left(42, "hey");

        os << left;

        REQUIRE(os.str() == "ExampleDto2{myFirstNumber=42,myName=hey}");
    }

    SECTION("should format using fmt") {
        ExampleDto2 left(42, "hey");

        REQUIRE(fmt::format("{}", left) == "ExampleDto2{myFirstNumber=42,myName=hey}");
    }

    SECTION("should format vector using fmt") {
        std::vector<ExampleDto2> dtos({{42, "hey"}});

        REQUIRE(fmt::format("{}", dtos) == "[ExampleDto2{myFirstNumber=42,myName=hey}]");
    }
}

TEST_CASE("CraygDto3::construct") {

    SECTION("should default construct") {
        ExampleDto3 examplePairDto;

        REQUIRE(examplePairDto.myFirstNumber == 0);
        REQUIRE(examplePairDto.myName == "");
    }

    SECTION("should construct with params") {
        ExampleDto3 examplePairDto(42, "hey", ExampleDto2(42, "hey"));

        REQUIRE(examplePairDto.myFirstNumber == 42);
        REQUIRE(examplePairDto.myName == "hey");
    }

    SECTION("should copy construct") {
        ExampleDto3 examplePairDto;
        ExampleDto3 other = examplePairDto;

        REQUIRE(other == examplePairDto);
    }
}

TEST_CASE("CraygDto3::compare") {

    SECTION("should be equal") {
        ExampleDto3 left(42, "hey", ExampleDto2(42, "hey"));
        ExampleDto3 right(42, "hey", ExampleDto2(42, "hey"));

        REQUIRE(left == right);
    }

    SECTION("should not be equal, different number") {
        ExampleDto3 left(41, "hey", ExampleDto2(42, "hey"));
        ExampleDto3 right(42, "hey", ExampleDto2(42, "hey"));

        REQUIRE(left != right);
    }

    SECTION("should not be equal, different name") {
        ExampleDto3 left(42, "hey", ExampleDto2(42, "hey"));
        ExampleDto3 right(42, "ho", ExampleDto2(42, "hey"));

        REQUIRE(left != right);
    }
}

TEST_CASE("CraygDto3::formatting") {

    SECTION("should format to ostream") {
        std::ostringstream os;
        ExampleDto3 left(42, "hey", ExampleDto2(42, "hey"));

        os << left;

        REQUIRE(
            os.str() == "ExampleDto3{myFirstNumber=42,myName=hey,nestedDto=ExampleDto2{myFirstNumber=42,myName=hey}}");
    }

    SECTION("should format using fmt") {
        ExampleDto3 left(42, "hey", ExampleDto2(42, "hey"));

        REQUIRE(fmt::format("{}", left)
                    == "ExampleDto3{myFirstNumber=42,myName=hey,nestedDto=ExampleDto2{myFirstNumber=42,myName=hey}}");
    }

    SECTION("should format vector of dto using fmt") {
        std::vector<ExampleDto3> dtos({{42, "hey", ExampleDto2(42, "hey")}});

        REQUIRE(fmt::format("{}", dtos)
                    == "[ExampleDto3{myFirstNumber=42,myName=hey,nestedDto=ExampleDto2{myFirstNumber=42,myName=hey}}]");
    }
}

}