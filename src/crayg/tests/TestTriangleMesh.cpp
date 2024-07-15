#include "fixtures/TriangleMeshFixtures.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerFacePrimVar.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"
#include <catch2/catch.hpp>
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
        std::size_t faceCount = cube.faceCount();

        REQUIRE(faceCount == 12);
    }
}

TEST_CASE("TriangleMesh::getBounds") {

    SECTION("bounds should be calculated corretly") {
        TriangleMesh triangleMesh;
        triangleMesh.points.emplace_back(0.f, 0.f, 0.f);
        triangleMesh.points.emplace_back(0.f, 1.f, 0.f);
        triangleMesh.points.emplace_back(1.f, 0.f, 0.f);
        triangleMesh.faceVertexIndices.emplace_back(0, 1, 2);
        triangleMesh.init();

        const BoundingBox boundingBox = triangleMesh.getBounds();

        REQUIRE(boundingBox == BoundingBox({0.f, 0.f, 0.f}, {1.f, 1.f, 0.f}));
    }
}

TEST_CASE("TriangleMesh::init") {
    TriangleMesh triangleMesh;
    triangleMesh.points.emplace_back(0.f, 0.f, 0.f);
    triangleMesh.points.emplace_back(0.f, 1.f, 0.f);
    triangleMesh.points.emplace_back(1.f, 0.f, 0.f);
    triangleMesh.faceVertexIndices.emplace_back(0, 1, 2);

    SECTION("not providing normals primvar should auto generate normals") {
        triangleMesh.init();

        REQUIRE(triangleMesh.normalsPrimVar != nullptr);
        REQUIRE(triangleMesh.getNormalsPrimVarAs<TriangleMeshPerFacePrimVar<Vector3f>>()->read(0) ==
                Vector3f(0, 0, -1));
    }

    SECTION("providing normals primvar should use them") {
        auto normalsPrimVar = triangleMesh.addNormalsPrimVar<TriangleMeshPerPointPrimVar<Vector3f>>();
        normalsPrimVar->write(0, Vector3f(1.f, 0.f, 0.f));
        triangleMesh.init();

        REQUIRE(triangleMesh.normalsPrimVar != nullptr);
        REQUIRE(normalsPrimVar->read(0) == Vector3f(1.f, 0.f, 0.f));
    }
}

TEST_CASE("TriangleMesh::faceIds") {
    TriangleMesh triangleMesh;
    SECTION("should iterate successfully over empty mesh") {
        std::vector<std::size_t> ids;

        std::copy(triangleMesh.faceIds().begin(), triangleMesh.faceIds().end(), std::back_inserter(ids));

        std::vector<std::size_t> expectedIds;
        REQUIRE(ids == expectedIds);
    }

    SECTION("should iterate successfully over all face ids of a cube") {
        TriangleMesh::createCube(triangleMesh);
        std::vector<std::size_t> ids;

        std::copy(triangleMesh.faceIds().begin(), triangleMesh.faceIds().end(), std::back_inserter(ids));

        std::vector<std::size_t> expectedIds;
        expectedIds.resize(12);
        std::iota(expectedIds.begin(), expectedIds.end(), 0);
        REQUIRE(ids == expectedIds);
    }
}

TEST_CASE("TriangleMesh::getPrimitives") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    std::vector<Imageable *> target;

    triangleMesh->getPrimitives(target);

    REQUIRE(target.size() == 4);
}

}
