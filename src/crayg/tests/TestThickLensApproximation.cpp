#include "fixtures/CameraLensFixtures.h"
#include "scene/camera/realistic/CameraLens.h"
#include "scene/camera/realistic/ThickLensApproximation.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ThickLensApproximationCalculator::calculate") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();
    CameraLens schneider30mm = CameraLensFixtures::createSchneider30mmAnamorphic();

    SECTION("should calculate vertical ThickLensApproximation correctly for Canon 70-200mm") {
        ThickLensApproximationCalculator calculator(canon70_200);

        auto thickLensApproximation = calculator.calculate(ThickLensApproximationCalculator::Direction::VERTICAL);

        const float focalLength = calculateEffectiveFocalLength(thickLensApproximation);
        REQUIRE(focalLength == Catch::Detail::Approx(7.21183792f));

        REQUIRE(thickLensApproximation.firstCardinalPoints.pZ == Catch::Detail::Approx(-7.4172355f));
        REQUIRE(thickLensApproximation.firstCardinalPoints.fZ == Catch::Detail::Approx(-0.205406189));
        REQUIRE(thickLensApproximation.secondCardinalPoints.pZ == Catch::Detail::Approx(-11.7357));
        REQUIRE(thickLensApproximation.secondCardinalPoints.fZ == Catch::Detail::Approx(-18.94753f));
    }

    SECTION("should calculate horizontal ThickLensApproximation correctly for Canon 70-200mm") {
        ThickLensApproximationCalculator calculator(canon70_200);

        auto thickLensApproximation = calculator.calculate(ThickLensApproximationCalculator::Direction::VERTICAL);

        const float focalLength = calculateEffectiveFocalLength(thickLensApproximation);
        REQUIRE(focalLength == Catch::Detail::Approx(7.21183792f));
    }

    SECTION("should calculate vertical ThickLensApproximation correctly for anamorphic Schneider 30mm") {
        ThickLensApproximationCalculator calculator(schneider30mm);

        auto thickLensApproximation = calculator.calculate(ThickLensApproximationCalculator::Direction::VERTICAL);

        const float focalLength = calculateEffectiveFocalLength(thickLensApproximation);
        REQUIRE(focalLength == Catch::Detail::Approx(6.05536f));
    }

    SECTION("should calculate horizontal ThickLensApproximation correctly for anamorphic Schneider 30mm") {
        ThickLensApproximationCalculator calculator(schneider30mm);

        auto thickLensApproximation = calculator.calculate(ThickLensApproximationCalculator::Direction::HORIZONTAL);

        const float focalLength = calculateEffectiveFocalLength(thickLensApproximation);
        REQUIRE(focalLength == Catch::Detail::Approx(3.14917f));
    }

    SECTION("should throw if aperture is too small") {
        canon70_200.changeAperture(50000000.f);
        ThickLensApproximationCalculator calculator(canon70_200);

        REQUIRE_THROWS_AS(calculator.calculate(ThickLensApproximationCalculator::Direction::VERTICAL),
                          std::runtime_error);
    }
}

}