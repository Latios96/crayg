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

TEST_CASE("TriangleMesh::faceCount") {
    TriangleMesh cube;
    TriangleMesh::createCube(cube);

    SECTION("should return correct face count for cube") {
        int faceCount = cube.faceCount();

        REQUIRE(faceCount == 12);
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

TEST_CASE("TriangleMesh::init") {
    TriangleMesh triangleMesh;
    triangleMesh.points.emplace_back(0, 0, 0);
    triangleMesh.points.emplace_back(0, 1, 0);
    triangleMesh.points.emplace_back(1, 0, 0);
    triangleMesh.faceIndices.push_back(0);
    triangleMesh.faceIndices.push_back(1);
    triangleMesh.faceIndices.push_back(2);

    SECTION("providing normals primvar should use this") {
        triangleMesh.init();

        REQUIRE(triangleMesh.normalsPrimVar != nullptr);
        REQUIRE(triangleMesh.normalsPrimVar->read(0) == Vector3f(0, 0, -1));
    }

    SECTION("not providing normals primvar should calculate") {
        triangleMesh.addNormalsPrimVar<TriangleMeshPerPointPrimVar<Vector3f>>();
        triangleMesh.normalsPrimVar->write(0, Vector3f(1, 0, 0));
        triangleMesh.init();

        REQUIRE(triangleMesh.normalsPrimVar != nullptr);
        REQUIRE(triangleMesh.normalsPrimVar->read(0) == Vector3f(1, 0, 0));
    }
}

}
