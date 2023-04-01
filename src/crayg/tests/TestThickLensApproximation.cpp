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

        REQUIRE(thickLensApproximation == ThickLensApproximation({8.794485, -8.882062}, {-43.471054, -48.73264}));
    }
}

}