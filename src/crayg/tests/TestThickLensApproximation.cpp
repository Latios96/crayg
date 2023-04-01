#include "fixtures/CameraLensFixtures.h"
#include "scene/camera/CameraLens.h"
#include "scene/camera/ThickLensApproximation.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ThickLensApproximationCalculator::calculate") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should calculate calculate ThickLensApproximation correctly for Canon 70-200mm") {
        ThickLensApproximationCalculator calculator(canon70_200);

        auto thickLensApproximation = calculator.calculate();

        REQUIRE(thickLensApproximation == ThickLensApproximation({8.794485f, -8.882062f}, {-43.471054f, -48.73264f}));
    }

    SECTION("should throw if aperture is too small") {
        canon70_200.elements[24].apertureRadius = 1e-5f;
        ThickLensApproximationCalculator calculator(canon70_200);

        REQUIRE_THROWS_AS(calculator.calculate(), std::runtime_error);
    }
}

}