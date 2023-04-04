#include "fixtures/CameraLensFixtures.h"
#include "scene/camera/CameraLens.h"
#include "scene/camera/ExitPupilCalculator.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ExitPupilCalculator::calculate") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should calculate exit pupils correctly for Canon 70-200mm") {
        ExitPupilCalculator exitPupilCalculator(canon70_200, 2.68328f, {10, 64, true});

        auto exitPupil = exitPupilCalculator.calculate();

        REQUIRE(exitPupil.pupilBounds.size() == 10);
    }
}

}