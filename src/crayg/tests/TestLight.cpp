#include <catch2/catch.hpp>
#include "scene/Light.h"

namespace crayg {

TEST_CASE("Light Sampling") {
    const float NO_SHADOW = 1.0f;
    const float FULL_SHADOW = 0.0f;

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("noIntersectionShouldReturnNoShadow") {
        Scene scene;
        fakeit::Mock<SceneIntersector> mockSceneIntersector;
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection::createInvalid());

        const float shadowFactor = light.calculateShadowFactor(mockSceneIntersector.get(), {0, 0, 0});
        REQUIRE(shadowFactor == NO_SHADOW);
    }

    SECTION("intersectionIsBehindLight") {
        Scene scene;
        fakeit::Mock<SceneIntersector> mockSceneIntersector;
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection(10,
                                                                                             std::make_shared<Sphere>()));

        const float shadowFactor = light.calculateShadowFactor(mockSceneIntersector.get(), {0, 0, 0});
        REQUIRE(shadowFactor == NO_SHADOW);
    }

    SECTION("intersectionIsBeforeLight") {
        Scene scene;
        fakeit::Mock<SceneIntersector> mockSceneIntersector;
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection(2,
                                                                                             std::make_shared<Sphere>()));

        const float shadowFactor = light.calculateShadowFactor(mockSceneIntersector.get(), {0, 0, 0});
        REQUIRE(shadowFactor == FULL_SHADOW);
    }
}

TEST_CASE("Light::radiance") {

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("should return correct radiance") {
        const Vector3f point(0, 0, 0);
        const Vector3f normal(0, 1, 0);

        auto radiance = light.radiance(point, normal);

        REQUIRE(radiance.radiance == Catch::Detail::Approx(0.2f));
        REQUIRE(radiance.ray == Ray({0, 0, 0}, {0, 5, 0}));
    }
}

}

