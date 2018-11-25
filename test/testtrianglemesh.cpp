//
// Created by Jan Honsbrok on 15.11.18.
//
#include <catch.hpp>
#include <scene/TriangeMesh.h>

TEST_CASE("TriangleIntersection"){
    TriangleMesh cube;
    TriangleMesh::createCube(cube);

    SECTION("intersect_"){
        Ray ray({0.99f,0.99f,-2}, {0,0,1});
        Ray hitRay = cube.intersect(ray);
        //REQUIRE(hitRay.isValid());
        Vector3f loc = hitRay.constructIntersectionPoint();

        Triangle tri({-1,0,0}, {1, 1, 0}, {1,0,0});
        Vector3f locTri = tri.intersect(ray).constructIntersectionPoint();

        Ray ray2({1.1f,1.1f,-2}, {0,0,1});
        Ray hitRay2 = cube.intersect(ray2);
        REQUIRE_FALSE(hitRay2.isValid());

    }
}
