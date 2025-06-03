#include "utils/BitCast.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("BitCast") {
    SECTION("should work for float") {
        auto bits = BitCast::floatingToBits<float, uint32_t>(42);

        auto restoredValue = BitCast::floatingFromBits<float, uint32_t>(bits);

        REQUIRE(restoredValue == 42);
    }

    SECTION("should work for double") {
        auto bits = BitCast::floatingToBits<double, uint64_t>(42);

        auto restoredValue = BitCast::floatingFromBits<double, uint64_t>(bits);

        REQUIRE(restoredValue == 42);
    }
}
}