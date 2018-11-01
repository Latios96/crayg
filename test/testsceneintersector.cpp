//
// Created by Jan Honsbrok on 01.11.18.
//

#include <catch.hpp>
#include <scene/Scene.h>
#include "intersectors/SceneIntersector.h"
#include "foundation/Ray.h"

TEST_CASE("SceneIntersector"){
    Scene scene;

    scene.addObject(new Sphere(Vector3f(1,0,0), 1));
    scene.addObject(new Sphere(Vector3f(-2,0,0), 1));

    SceneIntersector intersector(scene);

    SECTION("intersects"){
        // Rays which should be hits
        REQUIRE(intersector.intersects(Ray(Vector3f(1,0,-5), Vector3f(0,0,1))));
        REQUIRE(intersector.intersects(Ray(Vector3f(-2,0,-5), Vector3f(0,0,1))));

        // Rays which should not be hits
        REQUIRE(intersector.intersects(Ray(Vector3f(0,0,0), Vector3f(0,0,1))));
    }
}