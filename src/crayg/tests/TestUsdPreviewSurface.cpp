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
    }

    SECTION("should return weighted reflection") {
        UsdPreviewSurface usdPreviewSurface(Color::createBlack());
        usdPreviewSurface.metallic = 0.5;

        Lobes lobes;
        usdPreviewSurface.getLobes(surfaceInteraction, lobes);

        REQUIRE(lobes.diffuse.weight == Color::createGrey(0));
        REQUIRE(lobes.specular.weight == Color::createGrey(0.5));
    }
}

}