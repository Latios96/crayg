#include <catch2/catch.hpp>
#include "basics/Vector3f.h"
#include "basics/OrthonormalBasis.h"

namespace crayg {

TEST_CASE("OrthonormalBasis::toLocalCoordinates") {

    SECTION("should transform vector correctly") {
        auto testData = GENERATE(table<Vector3f, Vector3f>({{{0, 0, 0}, {0, 0, 0}}, {{0, 1, 0}, {1, 1, 0}}}));
        const auto orthonormalBasis = OrthonormalBasis({1, 0, 0}, {1, 1, 0}, {0, 0, 1});

        const auto transformed = orthonormalBasis.toLocalCoordinates(std::get<0>(testData));

        REQUIRE(transformed == std::get<1>(testData));
    }
}

}