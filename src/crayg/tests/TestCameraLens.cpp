#include "crayg/foundation/physics/Wavelengths.h"
#include "crayg/scene/camera/realistic/CameraLens.h"
#include "fixtures/CameraLensFixtures.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("CameraLens::construct") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("aperture surface should be accessible") {
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
        REQUIRE(canon70_200.metadata.surfaceCount == 34);
        REQUIRE(Catch::Detail::Approx(canon70_200.metadata.maximumAperture) == 3.4220621586f);
        REQUIRE(canon70_200.metadata.isAnamorphic == false);
        REQUIRE(canon70_200.metadata.squeeze == 1);
        REQUIRE(canon70_200.metadata.closestFocalDistance == Catch::Detail::Approx(32.95898f));
    }

    SECTION("should calculate metadata correctly for anamorphic lens") {
        CameraLens schneider30mm = CameraLensFixtures::createSchneider30mmAnamorphic();
        REQUIRE(schneider30mm.metadata.isAnamorphic == true);
        REQUIRE(schneider30mm.metadata.squeeze == Catch::Detail::Approx(1.91406f));
    }
}

TEST_CASE("CameraLens::getFirstSurfaceZ") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should calculate z depth for first surface correctly") {
        auto firstsurface = canon70_200.getFirstSurface();

        REQUIRE(firstsurface.center == Catch::Detail::Approx(23.752f));
    }
}

TEST_CASE("CameraLens::getLastSurfaceZ") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should calculate z depth for last surface correctly") {
        auto lastsurface = canon70_200.getLastSurface();

        REQUIRE(lastsurface.center == Catch::Detail::Approx(5.45f));
    }
}

TEST_CASE("CameraLens::traceFromFilmToWorld") {

    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should trace correctly along optical axis") {
        Ray rayIn({0, 0, 0}, {0, 0, 1});

        auto rayOut = *canon70_200.traceFromFilmToWorld(rayIn, FraunhoferLines::SODIUM.wavelength);

        REQUIRE(rayOut.startPoint.x == 0);
        REQUIRE(rayOut.startPoint.y == 0);
        REQUIRE(rayOut.startPoint.z == Catch::Detail::Approx(canon70_200.getFirstSurface().center));
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
        Ray rayIn({0, 0, canon70_200.getFirstSurface().center + 1}, {0, 0, -1});

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

    SECTION("should return the aperture surface") {
        const auto aperture = canon70_200.getAperture();

        REQUIRE(aperture.ior == 0);
        REQUIRE(aperture.center == Catch::Detail::Approx(11.839f));
    }
}

Vector3f pointOnFocalPlane(const CameraLens &cameraLens, float focalDistance) {
    const Vector3f pointOnLens = {0, 0.5, cameraLens.getLastSurface().center};
    const Vector3f pointOnFilm = {0, 0, 0};
    const Ray ray = {pointOnFilm, (pointOnLens - pointOnFilm).normalize()};
    const auto focusedRay = *cameraLens.traceFromFilmToWorld(ray, FraunhoferLines::SODIUM.wavelength);
    const float t = (focalDistance - cameraLens.getFirstSurface().center) / focusedRay.direction.z;
    return focusedRay.constructIntersectionPoint(t);
}

TEST_CASE("CameraLens::focusLens") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should focus lens at given focal distance") {
        auto focalPlanePoint = pointOnFocalPlane(canon70_200, 100.f);
        REQUIRE(std::abs(focalPlanePoint.y) > 0.31170f);

        canon70_200.focusLens(100.f);

        focalPlanePoint = pointOnFocalPlane(canon70_200, 100.f);
        REQUIRE(std::abs(focalPlanePoint.y) < 0.03270f);
    }

    SECTION("should clamp focus distance if closer than closest focal distance") {
        canon70_200.focusLens(10.f);

        const Ray fromFilmToWorld{{0, 0, -1}, {0, 0, 1}};
        REQUIRE(canon70_200.traceFromFilmToWorld(fromFilmToWorld, FraunhoferLines::SODIUM.wavelength));
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
        const Vector3f pointOnLens = {0, 0.9f, canon70_200.getLastSurface().center};
        const Vector3f pointOnFilm = {0, 0, 0};
        const Ray ray = {pointOnFilm, (pointOnLens - pointOnFilm).normalize()};

        REQUIRE(canon70_200.traceFromFilmToWorld(ray, FraunhoferLines::SODIUM.wavelength));

        canon70_200.changeAperture(20.f);

        REQUIRE_FALSE(canon70_200.traceFromFilmToWorld(ray, FraunhoferLines::SODIUM.wavelength));
    }
}

TEST_CASE("CameraLens::hasAsphericSurfaces") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();
    CameraLens edmondAsphericLens = CameraLensFixtures::createEdmondAsphericLens();

    SECTION("should return false") {
        REQUIRE_FALSE(canon70_200.hasAsphericSurfaces());
    }

    SECTION("should return true") {
        REQUIRE(edmondAsphericLens.hasAsphericSurfaces());
    }
}

TEST_CASE("CameraLens::length") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();

    SECTION("should return correct length") {
        REQUIRE_THAT(canon70_200.length(), Catch::WithinRel(23.752f, 0.1f));
    }
}

TEST_CASE("CameraLens::zoom") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();
    CameraLens edmondAsphericLens = CameraLensFixtures::createEdmondAsphericLens();

    SECTION("should have no effect on a lens with no focal length samples") {
        const float firstSurfaceCenterBeforeZoom = edmondAsphericLens.getSurfaceCenter(edmondAsphericLens.surfaces[0]);

        edmondAsphericLens.zoom(50.f);

        const float firstSurfaceCenterAfterZoom = edmondAsphericLens.getSurfaceCenter(edmondAsphericLens.surfaces[0]);
        REQUIRE(firstSurfaceCenterBeforeZoom == firstSurfaceCenterAfterZoom);
    }

    SECTION("should zoom Canon 70-200mm to 70mm") {
        canon70_200.zoom(70);

        REQUIRE_THAT(canon70_200.metadata.focalLength, Catch::WithinRel(7.1f, 0.1f));
    }

    SECTION("should zoom Canon 70-200mm to 100mm") {
        canon70_200.zoom(100);

        REQUIRE_THAT(canon70_200.metadata.focalLength, Catch::WithinRel(10.f, 0.1f));
    }

    SECTION("should zoom Canon 70-200mm to 135mm") {
        canon70_200.zoom(135);

        REQUIRE_THAT(canon70_200.metadata.focalLength, Catch::WithinRel(13.5f, 0.1f));
    }

    SECTION("should zoom Canon 70-200mm to 160mm") {
        canon70_200.zoom(160);

        REQUIRE_THAT(canon70_200.metadata.focalLength, Catch::WithinRel(16.0f, 0.1f));
    }

    SECTION("should zoom Canon 70-200mm to 194mm") {
        canon70_200.zoom(194);

        REQUIRE_THAT(canon70_200.metadata.focalLength, Catch::WithinRel(19.4f, 0.1f));
    }
}

}