//
// Created by jan on 30.12.18.
//
#include <catch2/catch.hpp>
#include <fakeit.hpp>
using namespace fakeit;
#include <intersectors/SceneIntersector.h>
#include <lightSamplers/PointLightSampler.h>

// for some reason fakeit did not work here
class MockSceneIntersector : public SceneIntersector {
 public:
    MockSceneIntersector(Scene &scene, const Imageable::Intersection &return_value)
        : SceneIntersector(scene) {
        this->return_value = return_value;
    }
    Imageable::Intersection intersect(const Ray &ray) const override {
        return return_value;
    };
 private:
    Imageable::Intersection return_value;
};

TEST_CASE("PointLightSampler") {
    const float NO_SHADOW = 1.0f;
    const float FULL_SHADOW = 0.0f;

    Light light;
    light.setPosition({0, 5, 0});
    light.setIntensity(1.0);

    SECTION("noIntersectionShouldReturnNoShadow") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, Imageable::Intersection::createInvalid());
        PointLightSampler pointLightSampler(mockIntersector, light);

        const float shadowFactor = pointLightSampler.calculateShadowFactor({0, 0, 0});
        REQUIRE(shadowFactor == NO_SHADOW);
    }

    SECTION("intersectionIsBehindLight") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, {10, std::make_shared<Sphere>()});
        PointLightSampler pointLightSampler(mockIntersector, light);

        const float shadowFactor = pointLightSampler.calculateShadowFactor({0, 0, 0});
        REQUIRE(shadowFactor == NO_SHADOW);
    }

    SECTION("intersectionIsBeforeLight") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, {2, std::make_shared<Sphere>()});
        PointLightSampler pointLightSampler(mockIntersector, light);

        const float shadowFactor = pointLightSampler.calculateShadowFactor({0, 0, 0});
        REQUIRE(shadowFactor == FULL_SHADOW);
    }
}

