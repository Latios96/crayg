#include "fixtures/CameraLensFixtures.h"
#include "scene/camera/CameraLens.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("CameraLens::getFirstElementZ") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should calculate z depth for first element correctly") {
        auto firstElement = canon70_200.getFirstElement();

        REQUIRE(firstElement.center == Catch::Detail::Approx(23.751997f));
    }
}

TEST_CASE("CameraLens::getLastElementZ") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should calculate z depth for last element correctly") {
        auto lastElement = canon70_200.getLastElement();

        REQUIRE(lastElement.center == Catch::Detail::Approx(5.45f));
    }
}

TEST_CASE("CameraLens::traceFromFilmToWorld") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should trace correctly along optical axis") {
        Ray rayIn({0, 0, 0}, {0, 0, 1});

        auto rayOut = *canon70_200.traceFromFilmToWorld(rayIn);

        REQUIRE(rayOut.startPoint.x == 0);
        REQUIRE(rayOut.startPoint.y == 0);
        REQUIRE(rayOut.startPoint.z == Catch::Detail::Approx(canon70_200.getFirstElement().center));
        REQUIRE(rayOut.direction.x == 0);
        REQUIRE(rayOut.direction.y == 0);
        REQUIRE(rayOut.direction.z == Catch::Detail::Approx(1));
    }
    // todo check why
    /*SECTION("should return empty optional for ray exceeding aperture") {
        Ray rayIn({2.2f, 0, 0}, {0, 0, 1});

        auto rayOut = canon70_200.traceFromFilmToWorld(rayIn);

        REQUIRE_FALSE(rayOut);
    }*/
}

TEST_CASE("CameraLens::traceFromWorldToFilm") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should trace correctly along optical axis") {
        Ray rayIn({0, 0, canon70_200.getFirstElement().center + 1}, {0, 0, -1});

        auto rayOut = *canon70_200.traceFromWorldToFilm(rayIn);

        REQUIRE(rayOut.startPoint.x == 0);
        REQUIRE(rayOut.startPoint.y == 0);
        REQUIRE(rayOut.startPoint.z == Catch::Detail::Approx(5.4500012f));
        REQUIRE(rayOut.direction.x == 0);
        REQUIRE(rayOut.direction.y == 0);
        REQUIRE(rayOut.direction.z == -1);
    }
    // todo check why
    /*SECTION("should return empty optional for ray exceeding aperture") {
        Ray rayIn({2.2f, 0, 0}, {0, 0, -1});

        auto rayOut = canon70_200.traceFromWorldToFilm(rayIn);

        REQUIRE_FALSE(rayOut);
    }*/
}

TEST_CASE("CameraLens::moveLensElements") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should move lenses in positive z direction") {
        REQUIRE(canon70_200.getFirstElement().center == Catch::Detail::Approx(23.751997f));
        REQUIRE(canon70_200.getLastElement().center == Catch::Detail::Approx(5.45f));

        canon70_200.moveLensElements(2);

        REQUIRE(canon70_200.getFirstElement().center == Catch::Detail::Approx(25.751997f));
        REQUIRE(canon70_200.getLastElement().center == Catch::Detail::Approx(7.45f));
    }
}

}