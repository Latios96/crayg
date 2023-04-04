#include "fixtures/CameraLensFixtures.h"
#include "fixtures/TemporaryDirectory.h"
#include "scene/camera/LensRaytracerTracer.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensRaytracerTracer::collect and emit") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should collect and emit") {
        TemporaryDirectory temporaryDirectory;
        LensRaytracerTracer lensRaytracerTracer("crayg-testing", canon70_200);

        lensRaytracerTracer.collect({{1, 2, 3}, {4, 5, 6}});

        lensRaytracerTracer.emit(temporaryDirectory.getPath());

        REQUIRE(boost::filesystem::exists(temporaryDirectory.getPath() / "crayg-testing.json"));
    }
}

}