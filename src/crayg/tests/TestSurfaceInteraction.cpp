#include "crayg/renderer/integrators/SurfaceInteraction.h"
#include "crayg/scene/primitives/Sphere.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("SurfaceInteraction::spawnRayFromSurface") {
    auto sphere = std::make_shared<Sphere>();
    const SurfaceInteraction surfaceInteraction(*sphere, {0, 0, 0}, {0, 1, 0}, {{0, 1, -1}, {0, -1, 1}});

    const Ray spawnedRay = surfaceInteraction.spawnRayFromSurface({1, 1, 1});

    REQUIRE(spawnedRay == Ray({0, 0, 0}, {1, 1, 1}));
}

TEST_CASE("SurfaceInteraction::spawnReflectionRayFromSurface") {
    auto sphere = std::make_shared<Sphere>();
    const SurfaceInteraction surfaceInteraction(*sphere, {0, 0, 0}, {0, 1, 0}, {{0, 1, -1}, {0, -1, 1}});

    const Ray spawnedRay = surfaceInteraction.spawnReflectionRayFromSurface();

    REQUIRE(spawnedRay == Ray({0, 0, 0}, {0, 1, 1}));
}

}