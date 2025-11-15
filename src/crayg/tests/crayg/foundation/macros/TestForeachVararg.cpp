#include "crayg/foundation/macros/ForeachVararg.h"

#include <catch2/catch.hpp>

namespace crayg {

#define CRAYG_FOREACH_VARARG_TEST_ADD_TO_SUM(v) sum += v;

TEST_CASE("ForeachVararg") {

    SECTION("should expand correctly") {
        int sum = 0;

        CRAYG_FOREACH_VARARG(CRAYG_FOREACH_VARARG_TEST_ADD_TO_SUM, 1, 2, 3, 4, 5, 6)

        REQUIRE(sum == 21);
    }
}

}
