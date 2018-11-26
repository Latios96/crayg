//
// Created by Jan Honsbrok on 15.11.18.
//
#include <catch.hpp>
#include <scene/TriangeMesh.h>

TEST_CASE("TriangleIntersection"){
    TriangleMesh cube;
    TriangleMesh::createCube(cube);

    SECTION("intersect_"){
        // todo whats this?
        /*Ray ray({0.99f,0.99f,-2}, {0,0,1});
        Ray hitRay = cube.intersect(ray);
        //REQUIRE(hitRay.isValid());
        Vector3f loc = hitRay.constructIntersectionPoint();

        Triangle tri({-1,0,0}, {1, 1, 0}, {1,0,0});
        Vector3f locTri = tri.intersect(ray).constructIntersectionPoint();*/

        Ray ray2({1.1f,1.1f,-2}, {0,0,1});
        const Imageable::Intersection intersection = cube.intersect(ray2);
        Vector3f hitLocation = ray2.constructIntersectionPoint(intersection.rayParameter);
        REQUIRE_FALSE(hitLocation.isValid());

    }
}
