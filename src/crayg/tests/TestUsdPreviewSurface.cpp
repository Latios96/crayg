#include "integrators/AbstractIntegrator.h"
#include "scene/primitives/Sphere.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include <catch2/catch.hpp>
#include <fakeit.hpp>

namespace crayg {

TEST_CASE("UsdPreviewSurface::evaluate") {
    auto sphere = std::make_shared<Sphere>();
    SurfaceInteraction surfaceInteraction(*sphere, {0, 0, 0}, {0, 1, 0}, {{1, 1, 0}, {-1, -1, 0}});

    SECTION("should return diffuse Color for only diffuse surface") {
        UsdPreviewSurface usdPreviewSurface(Color::createGrey(0.5f));

        Lobes lobes;
        usdPreviewSurface.getLobes(surfaceInteraction, lobes);

        REQUIRE(lobes.diffuse.weight == Color::createGrey(0.5f));
        REQUIRE(lobes.specular.weight == Color::createBlack());
        REQUIRE(lobes.metallic.weight == Color::createBlack());
    }

    SECTION("should return diffuse and spec for dielectric") {
        UsdPreviewSurface usdPreviewSurface(Color::createGrey(0.5f));
        usdPreviewSurface.specularColor = Color::createWhite();
        usdPreviewSurface.metallic = 0;

        Lobes lobes;
        usdPreviewSurface.getLobes(surfaceInteraction, lobes);

        REQUIRE(lobes.diffuse.weight == Color::createGrey(0.48585278f));
        REQUIRE(lobes.specular.weight == Color::createWhite());
        REQUIRE(lobes.metallic.weight == Color::createBlack());
    }

    SECTION("should return only metal for conductor") {
        UsdPreviewSurface usdPreviewSurface(Color::createGrey(0.5f));
        usdPreviewSurface.metallic = 1;

        Lobes lobes;
        usdPreviewSurface.getLobes(surfaceInteraction, lobes);

        REQUIRE(lobes.diffuse.weight == Color::createBlack());
        REQUIRE(lobes.specular.weight == Color::createBlack());
        REQUIRE(lobes.metallic.weight == Color::createGrey(0.5));
    }
}

}