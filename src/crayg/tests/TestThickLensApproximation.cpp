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
        const float focalLength =
            thickLensApproximation.firstCardinalPoints.fZ - thickLensApproximation.firstCardinalPoints.pZ;
        REQUIRE(focalLength == Catch::Detail::Approx(7.21183792f)); // todo extract method for this
        // todo approx comparison
        REQUIRE(thickLensApproximation.firstCardinalPoints.pZ == Catch::Detail::Approx(-7.4172355f));
        REQUIRE(thickLensApproximation.firstCardinalPoints.fZ == Catch::Detail::Approx(-0.20541f));
        REQUIRE(thickLensApproximation.secondCardinalPoints.pZ == Catch::Detail::Approx(-20.77879f)); // todo check this
        REQUIRE(thickLensApproximation.secondCardinalPoints.fZ == Catch::Detail::Approx(-27.39604f));
    }
    // todo check why
    /*SECTION("should throw if aperture is too small") {
        canon70_200.elements[24].apertureRadius = 1e-25f;
        ThickLensApproximationCalculator calculator(canon70_200);

        REQUIRE_THROWS_AS(calculator.calculate(), std::runtime_error);
    }*/
}

}