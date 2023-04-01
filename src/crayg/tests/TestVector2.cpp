#include "basics/Vector2.h"
#include <catch2/catch.hpp>
#include <sstream>

namespace crayg {

TEST_CASE("Vector2::construction") {

    SECTION("should default construct to 0") {
        Vector2i vec;

        REQUIRE(vec == Vector2i(0, 0));
    }

    SECTION("should construct from single arg correctly") {
        Vector2i vec(1);

        REQUIRE(vec == Vector2i(1));
    }

    SECTION("should construct from args correctly") {
        Vector2i vec(1, 2);

        REQUIRE(vec == Vector2i(1, 2));
    }

    SECTION("should copy construct correctly") {
        Vector2i vec(1, 2);
        Vector2i copy = vec;

        REQUIRE(copy == Vector2i(1, 2));
    }
}

TEST_CASE("Vector2::operator+") {
    Vector2i left(1, 2);
    Vector2i right(3, 4);

    REQUIRE(left + right == Vector2i(4, 6));
}

TEST_CASE("Vector2::operator-") {
    Vector2i left(1, 2);
    Vector2i right(2, 1);

    REQUIRE(left - right == Vector2i(-1, 1));
}

TEST_CASE("Vector2::operator*") {
    Vector2i vec(1, 2);

    REQUIRE(vec * 2 == Vector2i(2, 4));
}

TEST_CASE("Vector2::operator/") {
    Vector2i vec(1, 2);

    REQUIRE(vec / 2 == Vector2i(0, 1));
}

TEST_CASE("Vector2::operator==") {
    SECTION("should be equal") {
        Vector2i left(1, 2);
        Vector2i right(1, 2);

        REQUIRE(left == right);
    }

    SECTION("should not be equal") {
        Vector2i left(1, 2);
        Vector2i right(2, 1);

        REQUIRE(left != right);
    }
}

TEST_CASE("Vector2::formatting") {
    SECTION("should be ostreamable") {
        std::ostringstream os;
        Vector2i vec(1, 2);

        os << vec;

        REQUIRE(os.str() == "Vector2{x=1,y=2}");
    }

    SECTION("should be formatable") {
        Vector2i vec(1, 2);

        REQUIRE(fmt::format("{}", vec) == "Vector2{x=1,y=2}");
    }
}

}