#include "crayg/imaging/CameraLens.h"
#include "crayg/imaging/ExitPupilCalculator.h"
#include "fixtures/CameraLensFixtures.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ExitPupilCalculator::calculate") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should calculate exit pupils correctly for Canon 70-200mm") {
        TaskReporter taskReporter;
        ExitPupilCalculator exitPupilCalculator(canon70_200, 2.68328f, {10, 64, true}, taskReporter);

        auto exitPupil = exitPupilCalculator.calculate();

        REQUIRE(exitPupil.pupilBounds.size() == 10);
    }
}

}