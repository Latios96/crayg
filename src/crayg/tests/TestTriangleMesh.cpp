#include <catch2/catch.hpp>
#include "scene/trianglemesh/TriangleMesh.h"
#include "scene/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"
#include <numeric>

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
        triangleMesh.faceVertexIndices.emplace_back(0, 1, 2);
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
    triangleMesh.faceVertexIndices.emplace_back(0, 1, 2);

    SECTION("providing normals primvar should use this") {
        triangleMesh.init();

        REQUIRE(triangleMesh.normalsPrimVar != nullptr);
        REQUIRE(
            triangleMesh.getNormalsPrimVarAs<TriangleMeshPerPointPrimVar<Vector3f>>()->read(0) == Vector3f(0, 0, -1));
    }

    SECTION("not providing normals primvar should calculate") {
        auto normalsPrimVar = triangleMesh.addNormalsPrimVar<TriangleMeshPerPointPrimVar<Vector3f>>();
        normalsPrimVar->write(0, Vector3f(1, 0, 0));
        triangleMesh.init();

        REQUIRE(triangleMesh.normalsPrimVar != nullptr);
        REQUIRE(normalsPrimVar->read(0) == Vector3f(1, 0, 0));
    }
}

TEST_CASE("TriangleMesh::faceIds") {
    TriangleMesh triangleMesh;
    SECTION("should iterate successfully over empty mesh") {
        std::vector<std::size_t> ids;

        std::copy(triangleMesh.faceIds().begin(), triangleMesh.faceIds().end(), std::back_inserter(ids));

        std::vector<std::size_t> expectedIds;
        REQUIRE(ids == expectedIds);
    }SECTION("should iterate successfully over all face ids of a cube") {
        TriangleMesh::createCube(triangleMesh);
        std::vector<std::size_t> ids;

        std::copy(triangleMesh.faceIds().begin(), triangleMesh.faceIds().end(), std::back_inserter(ids));

        std::vector<std::size_t> expectedIds;
        expectedIds.resize(12);
        std::iota(expectedIds.begin(), expectedIds.end(), 0);
        REQUIRE(ids == expectedIds);
    }
}

}
