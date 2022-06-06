#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include "scene/Light.h"
#include "intersectors/SceneIntersector.h"


namespace crayg {


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

TEST_CASE("Light Sampling") {
    const float NO_SHADOW = 1.0f;
    const float FULL_SHADOW = 0.0f;

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("noIntersectionShouldReturnNoShadow") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = light.calculateShadowFactor(mockIntersector, {0, 0, 0});
        REQUIRE(shadowFactor == NO_SHADOW);
    }

    SECTION("intersectionIsBehindLight") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, {10, std::make_shared<Sphere>()});

        const float shadowFactor = light.calculateShadowFactor(mockIntersector, {0, 0, 0});
        REQUIRE(shadowFactor == NO_SHADOW);
    }

    SECTION("intersectionIsBeforeLight") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, {2, std::make_shared<Sphere>()});

        const float shadowFactor = light.calculateShadowFactor(mockIntersector, {0, 0, 0});
        REQUIRE(shadowFactor == FULL_SHADOW);
    }
}

}

