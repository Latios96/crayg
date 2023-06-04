#include "fixtures/CameraLensFixtures.h"
#include "scene/camera/CameraLens.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("CameraLens::getFirstElementZ") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should calculate z depth for first element correctly") {
        auto firstElement = canon70_200.getFirstElement();

        REQUIRE(firstElement.center == Catch::Detail::Approx(23.752f));
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

    SECTION("should return empty optional for ray exceeding aperture") {
        Ray rayIn({2.2f, 0, 0}, {0, 0, 1});

        auto rayOut = canon70_200.traceFromFilmToWorld(rayIn);

        REQUIRE_FALSE(rayOut);
    }
}

TEST_CASE("CameraLens::traceFromWorldToFilm") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should trace correctly along optical axis") {
        Ray rayIn({0, 0, canon70_200.getFirstElement().center + 1}, {0, 0, -1});

        auto rayOut = *canon70_200.traceFromWorldToFilm(rayIn);

        REQUIRE(rayOut.startPoint.x == 0);
        REQUIRE(rayOut.startPoint.y == 0);
        REQUIRE(rayOut.startPoint.z == Catch::Detail::Approx(5.45f));
        REQUIRE(rayOut.direction.x == 0);
        REQUIRE(rayOut.direction.y == 0);
        REQUIRE(rayOut.direction.z == -1);
    }

    SECTION("should return empty optional for ray exceeding aperture") {
        Ray rayIn({2.2f, 0, 0}, {0, 0, -1});

        auto rayOut = canon70_200.traceFromWorldToFilm(rayIn);

        REQUIRE_FALSE(rayOut);
    }
}

TEST_CASE("CameraLens::moveLensElements") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should move lenses in positive z direction") {
        REQUIRE(canon70_200.getFirstElement().center == Catch::Detail::Approx(23.752f));
        REQUIRE(canon70_200.getLastElement().center == Catch::Detail::Approx(5.45f));

        canon70_200.moveLensElements(2);

        REQUIRE(canon70_200.getFirstElement().center == Catch::Detail::Approx(25.752f));
        REQUIRE(canon70_200.getLastElement().center == Catch::Detail::Approx(7.45f));
    }
}

TEST_CASE("CameraLens::getAperture") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should return the aperture element") {
        const auto aperture = canon70_200.getAperture();

        REQUIRE(aperture.ior == 0);
        REQUIRE(aperture.center == Catch::Detail::Approx(11.839f));
    }
}

Vector3f pointOnFocalPlane(const CameraLens &cameraLens, float focalDistance) {
    const Vector3f pointOnLens = {0, 0.5, cameraLens.getLastElement().center};
    const Vector3f pointOnFilm = {0, 0, 0};
    const Ray ray = {pointOnFilm, (pointOnLens - pointOnFilm).normalize()};
    const auto focusedRay = *cameraLens.traceFromFilmToWorld(ray);
    const float t = (focalDistance - cameraLens.getFirstElement().center) / focusedRay.direction.z;
    return focusedRay.constructIntersectionPoint(t);
}

TEST_CASE("CameraLens::focusLens") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should focus lens at given focal distance") {
        auto focalPlanePoint = pointOnFocalPlane(canon70_200, 100.f);
        REQUIRE(std::abs(focalPlanePoint.y) > 0.4f);

        canon70_200.focusLens(100.f);

        focalPlanePoint = pointOnFocalPlane(canon70_200, 100.f);
        REQUIRE(std::abs(focalPlanePoint.y) < 0.01f);
    }
}

TEST_CASE("CameraLens::changeAperture") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();
    // todo test clamping

    SECTION("changing the aperture should lead to rays that are cut off") {
        const Vector3f pointOnLens = {0, 0.9, canon70_200.getLastElement().center};
        const Vector3f pointOnFilm = {0, 0, 0};
        const Ray ray = {pointOnFilm, (pointOnLens - pointOnFilm).normalize()};

        REQUIRE(canon70_200.traceFromFilmToWorld(ray));

        // todo this should be extracted
        const float requestedApertureRadius = (7.12f / 20.f) / 2.0f;
        const float maximumApertureRadius = canon70_200.getAperture().apertureRadius;
        const float apertureRadius = std::clamp<float>(requestedApertureRadius, 0, maximumApertureRadius);
        canon70_200.getAperture().apertureRadius = apertureRadius;

        REQUIRE_FALSE(canon70_200.traceFromFilmToWorld(ray));
    }
}

}