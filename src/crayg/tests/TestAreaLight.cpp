#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <scene/Scene.h>
#include "scene/AreaLight.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

TEST_CASE("AreaLight::calculateShadowFactor") {

    class DummyAreaLight : public AreaLight {
     public:
        Vector3f sampleLightShape() const override {
            return transform.toPosition();
        }
        Vector3f getNormal(Vector3f point) override {
            return transform.applyForNormal({0, 0, 1});
        }
    };

    DummyAreaLight dummyAreaLight;
    dummyAreaLight.setPosition({0, 2, 2});
    dummyAreaLight.setIntensity(1);

    SECTION("should illuminate point in front of the areaLight when there are no objects inbetween") {
        Vector3f point(0, 2, 4);
        fakeit::Mock<SceneIntersector> mockSceneIntersector;
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection::createInvalid());

        const float shadowFactor = dummyAreaLight.calculateShadowFactor(mockSceneIntersector.get(), point);

        REQUIRE(shadowFactor == 1.0f);
    }

    SECTION("should not illuminate point in back of the areaLight when there are no objects inbetween") {
        Vector3f point(0, 2, 1.9f);
        fakeit::Mock<SceneIntersector> mockSceneIntersector;
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection::createInvalid());

        const float shadowFactor = dummyAreaLight.calculateShadowFactor(mockSceneIntersector.get(), point);

        REQUIRE(shadowFactor == 0);
    }

    SECTION("should not illuminate point in front of the areaLight when there are objects inbetween") {
        Vector3f point(0, 2, 4);
        fakeit::Mock<SceneIntersector> mockSceneIntersector;
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection(1, std::make_shared<Sphere>()));

        const float shadowFactor = dummyAreaLight.calculateShadowFactor(mockSceneIntersector.get(), point);

        REQUIRE(shadowFactor == 0);
    }

    SECTION("should illuminate point in front of the areaLight when there are objects inbetween") {
        Vector3f point(0, 2, 4);
        fakeit::Mock<SceneIntersector> mockSceneIntersector;
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection(1, std::make_shared<Sphere>()));

        const float shadowFactor = dummyAreaLight.calculateShadowFactor(mockSceneIntersector.get(), point);

        REQUIRE(shadowFactor == 0);
    }
}

}

