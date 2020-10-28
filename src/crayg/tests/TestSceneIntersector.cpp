//
// Created by Jan Honsbrok on 01.11.18.
//

#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include "intersectors/SceneIntersector.h"

TEST_CASE("SceneIntersector") {
    Scene scene;

    scene.addObject(std::make_shared<Sphere>(Vector3f(1, 0, 0), 1));
    scene.addObject(std::make_shared<Sphere>(Vector3f(-2, 0, 0), 1));

    SceneIntersector intersector(scene);

    SECTION("isIntersectingReturnsTrue") {
        REQUIRE(intersector.isIntersecting(Ray(Vector3f(1, 0, -5), Vector3f(0, 0, 1))));
        REQUIRE(intersector.isIntersecting(Ray(Vector3f(-2, 0, -5), Vector3f(0, 0, 1))));
        REQUIRE(intersector.isIntersecting(Ray(Vector3f(0, 0, 0), Vector3f(0, 0, 1))));
    }
}