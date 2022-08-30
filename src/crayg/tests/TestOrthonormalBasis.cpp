#include <catch2/catch.hpp>
#include "basics/Vector3f.h"
#include "basics/OrthonormalBasis.h"

namespace crayg {

TEST_CASE("OrthonormalBasis::construct") {

    SECTION("should construct an OrthonormalBasis correctly from single vector") {
        auto testData = GENERATE(table<Vector3f, OrthonormalBasis>({{{0, 1, 0}, {{-1, 0, 0}, {0, 0, -1}, {0, 1, 0}}},
                                                                    {Vector3f({1, 1, 0}).normalize(),
                                                                     {{-0.49999997, 0.49999997, 0}, {0, 0, -0.70710677},
                                                                      {0.70710677, 0.70710677, 0}}}}));

        const auto orthonormalBasis = OrthonormalBasis((std::get<0>(testData)));

        REQUIRE(orthonormalBasis == std::get<1>(testData));
        REQUIRE(orthonormalBasis.u.dot(orthonormalBasis.v) == 0);
        REQUIRE(orthonormalBasis.v.dot(orthonormalBasis.w) == 0);
        REQUIRE(orthonormalBasis.u.dot(orthonormalBasis.w) == 0);
    }
}

TEST_CASE("OrthonormalBasis::toLocalCoordinates") {

    SECTION("should transform vector correctly") {
        auto testData = GENERATE(table<Vector3f, Vector3f>({{{0, 0, 0}, {0, 0, 0}}, {{0, 1, 0}, {1, 1, 0}}}));
        const auto orthonormalBasis = OrthonormalBasis({1, 0, 0}, {1, 1, 0}, {0, 0, 1});

        const auto transformed = orthonormalBasis.toLocalCoordinates(std::get<0>(testData));

        REQUIRE(transformed == std::get<1>(testData));
    }
}

}