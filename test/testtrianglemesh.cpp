//
// Created by Jan Honsbrok on 15.11.18.
//
#include <catch.hpp>
#include <scene/TriangeMesh.h>

TEST_CASE("TriangleIntersection"){
    TriangleMesh cube;
    TriangleMesh::createCube(cube);

    SECTION("intersect_"){
        Ray ray({1.1f,1.1f,-2}, {0,0,1});
        const Imageable::Intersection intersection = cube.intersect(ray);
        Vector3f hitLocation = ray.constructIntersectionPoint(intersection.rayParameter);
        REQUIRE_FALSE(hitLocation.isValid());
    }
}
