#include "crayg/scene/lights/shapegenerators/DiskLightShapeGenerator.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("DiskLightShapeGenerator::getPointCount") {

    SECTION("should return correct point count") {
        DiskLight diskLight;
        DiskLightShapeGenerator diskLightShapeGenerator(diskLight, 8);

        REQUIRE(diskLightShapeGenerator.getPointCount() == 9);
    }
}

TEST_CASE("DiskLightShapeGenerator::getIndicesCount") {

    SECTION("should return correct indices count") {
        DiskLight diskLight;
        DiskLightShapeGenerator diskLightShapeGenerator(diskLight, 8);

        REQUIRE(diskLightShapeGenerator.getIndicesCount() == 8);
    }
}

TEST_CASE("DiskLightShapeGenerator::generateShape") {

    SECTION("should generate correct shape") {
        DiskLight diskLight;
        diskLight.setTransform(Transform::withPosition({0, 0, 0}));
        diskLight.setRadius(2);

        DiskLightShapeGenerator diskLightShapeGenerator(diskLight, 4);
        std::vector<Vector3f> points(diskLightShapeGenerator.getPointCount());
        std::vector<TriangleMesh::FaceVertexIndices> indices(diskLightShapeGenerator.getIndicesCount());

        diskLightShapeGenerator.generateShape(points.data(), indices.data());

        REQUIRE(points[0] == Vector3f(0, 0, 0));
        for (int i = 1; i < points.size(); i++) {
            REQUIRE(points[i].length() == Catch::Detail::Approx(2.0f));
        }

        REQUIRE(indices == std::vector<TriangleMesh::FaceVertexIndices>({{0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {3, 1, 0}}));
    }
}

}