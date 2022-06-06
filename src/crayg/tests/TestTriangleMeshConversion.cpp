#include <catch2/catch.hpp>
#include "scene/GroundPlane.h"
#include "scene/TriangleMesh.h"
#include "scene/TriangleMeshConversion.h"
#include "scene/DiffuseMaterial.h"

namespace crayg {

TEST_CASE("TriangleMeshConversion::toTriangleMesh") {

    SECTION("should convert GroundPlace correctly") {
        auto material = std::make_shared<DiffuseMaterial>("groundPlaneMat", Color::createGrey(0.5f));
        GroundPlane groundPlane;
        groundPlane.setTransform(Transform::withPosition({0, 1, 0}));
        groundPlane.setMaterial(material);
        TriangleMesh triangleMesh;

        TriangleMeshConversion::toTriangleMesh(groundPlane, triangleMesh);

        REQUIRE(triangleMesh.getTransform().toPosition() == Vector3f(0, 1, 0));
        REQUIRE(triangleMesh.points
                    == std::vector<Vector3f>({{-1000, 1, -1000}, {-1000, 1, 1000}, {1000, 1, 1000}, {1000, 1, -1000}}));
        REQUIRE(triangleMesh.faceIndices == std::vector<int>({0, 1, 2, 2, 3, 0}));
        REQUIRE(triangleMesh.getMaterial()->getName() == "groundPlaneMat");
    }
}
}