#include <catch2/catch.hpp>
#include "scene/Light.h"

namespace crayg {

TEST_CASE("Light::radiance") {

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("should return correct radiance") {
        const Vector3f point(0, 0, 0);
        const Vector3f normal(0, 1, 0);

        auto radiance = light.radiance(point, normal);

        REQUIRE(radiance.radiance == Catch::Detail::Approx(0.2f));
        REQUIRE(radiance.ray == Ray({0, 0, 0}, {0, 5, 0}));
    }
}

}

