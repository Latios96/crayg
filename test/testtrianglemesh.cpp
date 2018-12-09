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
    
    /*SECTION("testTransform"){
        Triangle triangle({2,0,0}, {2,1,0}, {2,1,1});
        Ray ray({3,0.25,0}, {-1,0,0});
        auto intersection = triangle.intersect(ray);
        REQUIRE(intersection.rayParameter == 5);
    }
    SECTION("testTransformBackfacing"){
        Triangle triangle({2,0,0}, {2,1,0}, {2,1,1});
        Ray ray({-2,0.25,0}, {1,0,0});
        auto intersection = triangle.intersect(ray);
        REQUIRE(intersection.rayParameter > 3);
    }*/
}
