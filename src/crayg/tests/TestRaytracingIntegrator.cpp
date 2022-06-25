#include <catch2/catch.hpp>
#include <integrators/RaytracingIntegrator.h>
#include <fakeit.hpp>

namespace crayg {

TEST_CASE("RaytracingIntegrator::calculateDirectLight") {
    fakeit::Mock<SceneIntersector> mockSceneIntersector;
    fakeit::Fake((mockSceneIntersector.dtor()));
    auto sceneIntersector = std::shared_ptr<SceneIntersector>(&mockSceneIntersector.get());
    Scene scene;
    RaytracingIntegrator raytracingIntegrator(scene, sceneIntersector);

    auto light = std::make_shared<Light>(Transform::withPosition({0, 2, 0}), 10.0f);

    SECTION("should calculate direct light for light correctly") {
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection::createInvalid());

        const float lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, 1, 0});

        REQUIRE(lightContribution == Catch::Detail::Approx(5.0025));
    }

    SECTION("should short circuit if intensity is 0") {
        light->setIntensity(0);

        const float lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, 1, 0});

        REQUIRE(lightContribution == 0);
        fakeit::Verify(Method(mockSceneIntersector, intersect)).Never();
    }

    SECTION("should short circuit if angle is to large") {
        const float lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, -1, 0});

        REQUIRE(lightContribution == 0);
        fakeit::Verify(Method(mockSceneIntersector, intersect)).Never();
    }

    SECTION("should return 0 iif light is occluded") {
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection(1,
                                                                                             std::make_shared<Sphere>(
                                                                                                 Vector3f(),
                                                                                                 1.0f)));

        const float lightContribution = raytracingIntegrator.calculateDirectLight(light, {0, 0, 0}, {0, -1, 0});

        REQUIRE(lightContribution == 0);
    }
}

}