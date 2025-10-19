#include "crayg/scene/camera/Camera.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("field of view") {
    SECTION("get horizontal field of view") {
        float focalLength = 36;
        float filmbackSize = 36.0f;
        Camera camera(Transform(), focalLength, filmbackSize);

        const float horizontalFieldOfViewInRadians = camera.getHorizontalFieldOfView();

        REQUIRE(horizontalFieldOfViewInRadians == Catch::Detail::Approx(0.92729343));
    }
}

}