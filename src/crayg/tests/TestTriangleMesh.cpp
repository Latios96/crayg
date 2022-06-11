#include <catch2/catch.hpp>
#include <scene/TriangleMesh.h>

namespace crayg {

TEST_CASE("TriangleMesh::intersect") {
    TriangleMesh cube;
    TriangleMesh::createCube(cube);

    SECTION("should not intersect with ray") {
        Ray ray({1.1f, 1.1f, -2}, {0, 0, 1});

        const Imageable::Intersection intersection = cube.intersect(ray);

        Vector3f hitLocation = ray.constructIntersectionPoint(intersection.rayParameter);
        REQUIRE_FALSE(hitLocation.isValid());
    }
}

TEST_CASE("TriangleMesh::getBounds") {

    SECTION("bounds should be calculated corretly") {
        TriangleMesh triangleMesh;
        triangleMesh.points.emplace_back(0, 0, 0);
        triangleMesh.points.emplace_back(0, 1, 0);
        triangleMesh.points.emplace_back(1, 0, 0);
        triangleMesh.faceIndices.push_back(0);
        triangleMesh.faceIndices.push_back(1);
        triangleMesh.faceIndices.push_back(2);
        triangleMesh.init();

        const BoundingBox boundingBox = triangleMesh.getBounds();

        REQUIRE(boundingBox == BoundingBox({0, 0, 0}, {1, 1, 0}));
    }
}

}
