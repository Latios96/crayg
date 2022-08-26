#include <catch2/catch.hpp>
#include <integrators/SurfaceInteraction.h>

namespace crayg {

TEST_CASE("SurfaceInteraction::spawnRayFromSurface") {
    const SurfaceInteraction surfaceInteraction({0, 0, 0}, {0, 1, 0}, {{0, 1, -1}, {0, -1, 1}});

    const Ray spawnedRay = surfaceInteraction.spawnRayFromSurface({1, 1, 1});

    REQUIRE(spawnedRay == Ray({0, 0, 0}, {1, 1, 1}));
}

TEST_CASE("SurfaceInteraction::spawnReflectionRayFromSurface") {
    const SurfaceInteraction surfaceInteraction({0, 0, 0}, {0, 1, 0}, {{0, 1, -1}, {0, -1, 1}});

    const Ray spawnedRay = surfaceInteraction.spawnReflectionRayFromSurface();

    REQUIRE(spawnedRay == Ray({0, 0, 0}, {0, 1, 1}));
}

}