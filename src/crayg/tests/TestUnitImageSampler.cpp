#include <catch2/catch.hpp>
#include <samplers/UnitSphereSampler.h>

namespace crayg {

TEST_CASE("UnitImageSampler") {

    SECTION("pointShouldBeInOnUnitSphere") {
        for (int i = 0; i < 10000; i++) {
            const Vector3f point = UnitSphereSampler::randomPointInside();
            REQUIRE(point.length() < 1);
        }
    }
}

}

