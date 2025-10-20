#include "crayg/scene/lights/shapegenerators/RectLightShapeGenerator.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("RectLightShapeGenerator::getPointCount") {

    SECTION("should return correct point count") {
        RectLight rectLight;
        RectLightShapeGenerator rectLightShapeGenerator(rectLight);

        REQUIRE(rectLightShapeGenerator.getPointCount() == 4);
    }
}

TEST_CASE("RectLightShapeGenerator::getIndicesCount") {

    SECTION("should return correct indices count") {
        RectLight rectLight;
        RectLightShapeGenerator rectLightShapeGenerator(rectLight);

        REQUIRE(rectLightShapeGenerator.getIndicesCount() == 2);
    }
}

TEST_CASE("RectLightShapeGenerator::generateShape") {

    SECTION("should generate correct shape") {
        RectLight rectLight;
        rectLight.setTransform(Transform::withPosition({0, 1, 0}));
        rectLight.setWidth(2);
        rectLight.setHeight(3);

        RectLightShapeGenerator rectLightShapeGenerator(rectLight);
        std::vector<Vector3f> points(rectLightShapeGenerator.getPointCount());
        std::vector<TriangleMesh::FaceVertexIndices> indices(rectLightShapeGenerator.getIndicesCount());

        rectLightShapeGenerator.generateShape(points.data(), indices.data());

        REQUIRE(points == std::vector<Vector3f>(
                              {{-1, -0.5f, -0.001f}, {-1, 2.5f, -0.001f}, {1, 2.5f, -0.001f}, {1, -0.5f, -0.001f}}));
        REQUIRE(indices == std::vector<TriangleMesh::FaceVertexIndices>({{2, 1, 0}, {3, 2, 0}}));
    }
}

}