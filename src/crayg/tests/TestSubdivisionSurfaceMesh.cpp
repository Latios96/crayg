#include "fixtures/SubdivisionSurfaceMeshFixtures.h"
#include "scene/materials/UsdPreviewSurface.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include <catch2/catch.hpp>

namespace crayg {

Ray RAY_TO_INTERSECT = Ray({0, 1, 0}, {0, -1, 0});

TEST_CASE("SubdivisionSurfaceMesh::getNormal") {

    SubdivisionSurfaceMesh subdivisionSurfaceMesh;
    SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);

    SECTION("should throw because mesh was not tessellated yet") {
        REQUIRE_THROWS_AS(subdivisionSurfaceMesh.getNormal({0, 0, 0}), std::runtime_error);
    }

    SECTION("should delegate to TriangleMesh") {
        subdivisionSurfaceMesh.tessellate();
        subdivisionSurfaceMesh.getNormal({0, 0, 0});
    }
}

TEST_CASE("SubdivisionSurfaceMesh::intersect") {

    SubdivisionSurfaceMesh subdivisionSurfaceMesh;
    SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);

    SECTION("should throw because mesh was not tessellated yet") {
        REQUIRE_THROWS_AS(subdivisionSurfaceMesh.intersect(RAY_TO_INTERSECT), std::runtime_error);
    }

    SECTION("should delegate to TriangleMesh") {
        subdivisionSurfaceMesh.tessellate();
        subdivisionSurfaceMesh.intersect(RAY_TO_INTERSECT);
    }
}

TEST_CASE("SubdivisionSurfaceMesh::isIntersecting") {

    SubdivisionSurfaceMesh subdivisionSurfaceMesh;
    SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);

    SECTION("should throw because mesh was not tessellated yet") {
        REQUIRE_THROWS_AS(subdivisionSurfaceMesh.isIntersecting(RAY_TO_INTERSECT), std::runtime_error);
    }

    SECTION("should delegate to TriangleMesh") {
        subdivisionSurfaceMesh.tessellate();
        subdivisionSurfaceMesh.isIntersecting(RAY_TO_INTERSECT);
    }
}

TEST_CASE("SubdivisionSurfaceMesh::getBounds") {

    SubdivisionSurfaceMesh subdivisionSurfaceMesh;
    SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);

    SECTION("should throw because mesh was not tessellated yet") {
        REQUIRE_THROWS_AS(subdivisionSurfaceMesh.getBounds(), std::runtime_error);
    }

    SECTION("should delegate to TriangleMesh") {
        subdivisionSurfaceMesh.tessellate();
        subdivisionSurfaceMesh.getBounds();
    }
}

TEST_CASE("SubdivisionSurfaceMesh::getPrimitives") {

    SubdivisionSurfaceMesh subdivisionSurfaceMesh;
    SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);
    std::vector<Imageable *> target;
    bool isOwning;

    SECTION("should throw because mesh was not tessellated yet") {
        REQUIRE_THROWS_AS(subdivisionSurfaceMesh.getPrimitives(target, &isOwning), std::runtime_error);
    }

    SECTION("should delegate to TriangleMesh") {
        subdivisionSurfaceMesh.tessellate();
        subdivisionSurfaceMesh.getPrimitives(target, &isOwning);
    }
}

TEST_CASE("SubdivisionSurfaceMesh::primitiveCount") {

    SubdivisionSurfaceMesh subdivisionSurfaceMesh;
    SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);

    SECTION("should throw because mesh was not tessellated yet") {
        REQUIRE_THROWS_AS(subdivisionSurfaceMesh.primitiveCount(), std::runtime_error);
    }

    SECTION("should delegate to TriangleMesh") {
        subdivisionSurfaceMesh.tessellate();
        subdivisionSurfaceMesh.primitiveCount();
    }
}

TEST_CASE("SubdivisionSurfaceMesh::faceCount") {

    SECTION("should return correct faceCount for cube") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createUnitCube(subdivisionSurfaceMesh);

        REQUIRE(subdivisionSurfaceMesh.faceCount() == 6);
    }

    SECTION("should return correct faceCount for plane") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);

        REQUIRE(subdivisionSurfaceMesh.faceCount() == 1);
    }
}

TEST_CASE("SubdivisionSurfaceMesh::tessellate") {

    SECTION("should tessellate correctly") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        auto usdPreviewSurface = std::make_shared<UsdPreviewSurface>(Color::createWhite());
        subdivisionSurfaceMesh.setMaterial(usdPreviewSurface);
        const Transform transform = Transform::withPosition({0, 1, 0});
        subdivisionSurfaceMesh.setTransform(transform);
        SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);

        subdivisionSurfaceMesh.tessellate();

        REQUIRE(subdivisionSurfaceMesh.points.empty());
        REQUIRE(subdivisionSurfaceMesh.faceVertexIndices.empty());
        REQUIRE(subdivisionSurfaceMesh.faceVertexCounts.empty());
        REQUIRE(subdivisionSurfaceMesh.triangleMesh.points.size() == 81);
        REQUIRE(subdivisionSurfaceMesh.triangleMesh.faceVertexIndices.size() == 128);
        REQUIRE(subdivisionSurfaceMesh.triangleMesh.getMaterial() == usdPreviewSurface);
        REQUIRE(subdivisionSurfaceMesh.triangleMesh.getTransform() == transform);
    }
}

}