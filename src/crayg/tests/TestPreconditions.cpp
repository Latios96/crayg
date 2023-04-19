#include <catch2/catch.hpp>
#include <utils/Preconditions.h>

namespace crayg {

TEST_CASE("check unit vector", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_IS_NORMALIZED_VECTOR(Vector3f(1, 2, 3).normalize());
    }

    SECTION("should fail") {
        try {
            CRAYG_CHECK_IS_NORMALIZED_VECTOR(Vector3f(1, 2, 3));
            REQUIRE(false);
        } catch (std::exception &e) {
            REQUIRE(true);
        }
    }
}

TEST_CASE("check array index", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_IS_VALID_INDEX(0, 1);
        CRAYG_CHECK_IS_VALID_INDEX(0, 10);
        CRAYG_CHECK_IS_VALID_INDEX(1, 10);
        CRAYG_CHECK_IS_VALID_INDEX(3, 10);
    }

    SECTION("should fail") {
        const auto testData = GENERATE(table<int, int>({{-1, 0}, {0, 0}, {10, 10}, {11, 10}}));

        try {
            CRAYG_CHECK_IS_VALID_INDEX(std::get<0>(testData), std::get<1>(testData));
            REQUIRE(false);
        } catch (std::exception &e) {
            REQUIRE(true);
        }
    }
}

}
