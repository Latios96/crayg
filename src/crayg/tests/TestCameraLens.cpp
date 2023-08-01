#include "fixtures/CameraLensFixtures.h"
#include "scene/camera/realistic/CameraLens.h"
#include "scene/camera/realistic/Wavelengths.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("CameraLens::construct") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("aperture element should be accessible") {
        REQUIRE(canon70_200.getAperture().apertureRadius > 2);
        REQUIRE(canon70_200.getAperture().ior == 0);
    }

    SECTION("aperture radius should be at maximum opening") {
        REQUIRE(canon70_200.getApertureRadius() > 2.f);
    }

    SECTION("thick lens approximation should be populated") {
        REQUIRE(canon70_200.thickLensApproximation != ThickLensApproximation());
    }

    SECTION("focal length should be populated") {
        REQUIRE(canon70_200.metadata.focalLength >= 7);
    }

    SECTION("should calculate metadata on the fly") {
        REQUIRE(canon70_200.metadata.focalLength >= 7);
        REQUIRE(canon70_200.metadata.elementCount == 34);
        REQUIRE(Catch::Detail::Approx(canon70_200.metadata.maximumAperture) == 3.4739232063f);
        REQUIRE(canon70_200.metadata.isAnamorphic == false);
        REQUIRE(canon70_200.metadata.squeeze == 1);
    }

    SECTION("should calculate metadata correctly for anamorphic lens") {
        CameraLens schneider30mm = CameraLensFixtures::createSchneider30mmAnamorphic();
        REQUIRE(schneider30mm.metadata.isAnamorphic == true);
        REQUIRE(schneider30mm.metadata.squeeze == Catch::Detail::Approx(1.7848f));
    }
}

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

        auto rayOut = *canon70_200.traceFromFilmToWorld(rayIn, FraunhoferLines::SODIUM.wavelength);

        REQUIRE(rayOut.startPoint.x == 0);
        REQUIRE(rayOut.startPoint.y == 0);
        REQUIRE(rayOut.startPoint.z == Catch::Detail::Approx(canon70_200.getFirstElement().center));
        REQUIRE(rayOut.direction.x == 0);
        REQUIRE(rayOut.direction.y == 0);
        REQUIRE(rayOut.direction.z == Catch::Detail::Approx(1));
    }

    SECTION("should return empty optional for ray exceeding aperture") {
        Ray rayIn({2.2f, 0, 0}, {0, 0, 1});

        auto rayOut = canon70_200.traceFromFilmToWorld(rayIn, FraunhoferLines::SODIUM.wavelength);

        REQUIRE_FALSE(rayOut);
    }
}

TEST_CASE("CameraLens::traceFromWorldToFilm") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should trace correctly along optical axis") {
        Ray rayIn({0, 0, canon70_200.getFirstElement().center + 1}, {0, 0, -1});

        auto rayOut = *canon70_200.traceFromWorldToFilm(rayIn, FraunhoferLines::SODIUM.wavelength);

        REQUIRE(rayOut.startPoint.x == 0);
        REQUIRE(rayOut.startPoint.y == 0);
        REQUIRE(rayOut.startPoint.z == Catch::Detail::Approx(5.45f));
        REQUIRE(rayOut.direction.x == 0);
        REQUIRE(rayOut.direction.y == 0);
        REQUIRE(rayOut.direction.z == -1);
    }

    SECTION("should return empty optional for ray exceeding aperture") {
        Ray rayIn({2.2f, 0, 0}, {0, 0, -1});

        auto rayOut = canon70_200.traceFromWorldToFilm(rayIn, FraunhoferLines::SODIUM.wavelength);

        REQUIRE_FALSE(rayOut);
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
    const auto focusedRay = *cameraLens.traceFromFilmToWorld(ray, FraunhoferLines::SODIUM.wavelength);
    const float t = (focalDistance - cameraLens.getFirstElement().center) / focusedRay.direction.z;
    return focusedRay.constructIntersectionPoint(t);
}

TEST_CASE("CameraLens::focusLens") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should focus lens at given focal distance") {
        auto focalPlanePoint = pointOnFocalPlane(canon70_200, 100.f);
        REQUIRE(std::abs(focalPlanePoint.y) > 0.31170f);

        canon70_200.focusLens(100.f);

        focalPlanePoint = pointOnFocalPlane(canon70_200, 100.f);
        REQUIRE(std::abs(focalPlanePoint.y) < 0.01170f);
    }
}

TEST_CASE("CameraLens::changeAperture") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should clamp fStop if this is too large") {
        REQUIRE(canon70_200.getApertureRadius() >= 2.f);

        canon70_200.changeAperture(1.f);

        REQUIRE(canon70_200.getApertureRadius() >= 2.f);
    }

    SECTION("changing the aperture should lead to rays that are cut off") {
        const Vector3f pointOnLens = {0, 0.9f, canon70_200.getLastElement().center};
        const Vector3f pointOnFilm = {0, 0, 0};
        const Ray ray = {pointOnFilm, (pointOnLens - pointOnFilm).normalize()};

        REQUIRE(canon70_200.traceFromFilmToWorld(ray, FraunhoferLines::SODIUM.wavelength));

        canon70_200.changeAperture(20.f);

        REQUIRE_FALSE(canon70_200.traceFromFilmToWorld(ray, FraunhoferLines::SODIUM.wavelength));
    }
}

}