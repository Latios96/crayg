#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <scene/Scene.h>
#include "scene/Light.h"
#include "intersectors/SceneIntersector.h"


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

}

