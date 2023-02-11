#include <catch2/catch.hpp>
#include <integrators/RaytracingIntegrator.h>
#include <fakeit.hpp>
#include "scene/primitives/Sphere.h"

namespace crayg {

TEST_CASE("RaytracingIntegrator::calculateDirectLight") {
    fakeit::Mock<SceneIntersector> mockSceneIntersector;
    fakeit::Fake((mockSceneIntersector.dtor()));
    auto sceneIntersector = std::shared_ptr<SceneIntersector>(&mockSceneIntersector.get());
    Scene scene;
    RaytracingIntegrator raytracingIntegrator(scene, sceneIntersector, IntegratorSettings());

    auto light = std::make_shared<Light>(Transform::withPosition({0, 2, 0}), 10.0f);

    SECTION("should calculate direct light for light correctly") {
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection::createInvalid());

        const Color lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, 1, 0});

        REQUIRE(lightContribution == Color::createGrey(5.0025015f));
    }

    SECTION("should respect Light color") {
        light->setColor({1, 0, 0});
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection::createInvalid());

        const Color lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, 1, 0});

        REQUIRE(lightContribution == Color({5.0025015f, 0, 0}));
    }

    SECTION("should short circuit if intensity is 0") {
        light->setIntensity(0);

        const Color lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, 1, 0});

        REQUIRE(lightContribution == Color::createBlack());
        fakeit::Verify(Method(mockSceneIntersector, intersect)).Never();
    }

    SECTION("should short circuit if angle is to large") {
        const Color lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, -1, 0});

        REQUIRE(lightContribution == Color::createBlack());
        fakeit::Verify(Method(mockSceneIntersector, intersect)).Never();
    }

    SECTION("should return 0 if light is occluded") {
        std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(Vector3f(), 1.0f);
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection(1, sphere.get()));

        const Color lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, -1, 0});

        REQUIRE(lightContribution == Color::createBlack());
    }
}

}