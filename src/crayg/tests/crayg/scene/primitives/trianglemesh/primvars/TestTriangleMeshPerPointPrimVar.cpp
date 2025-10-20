#include "crayg/scene/primitives/trianglemesh/TriangleMesh.h"
#include "crayg/scene/primitives/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"
#include "fixtures/TriangleMeshFixtures.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("TriangleMeshPerPointPrimVar::interpolateAt") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    SECTION("should interpolate constant value correctly") {
        TriangleMeshPerPointPrimVar<Color> primVar(*triangleMesh);
        primVar.allocate();
        primVar.write(0, Color::createGrey(0.5));
        primVar.write(1, Color::createGrey(0.5));
        primVar.write(2, Color::createGrey(0.5));
        primVar.write(3, Color::createGrey(0.5));

        Color interpolatedValue = primVar.interpolateAt(0, {-0.25, 0, 0.25});

        REQUIRE(interpolatedValue == Color::createGrey(0.5));
    }

    SECTION("should interpolate non-constant value correctly") {
        TriangleMeshPerPointPrimVar<Color> primVar(*triangleMesh);
        primVar.allocate();
        primVar.write(0, Color(1, 0, 0));
        primVar.write(1, Color(0, 1, 0));
        primVar.write(2, Color(0, 0, 1));
        primVar.write(3, Color(1, 0, 0));

        Color interpolatedValue = primVar.interpolateAt(0, {-0.25, 0, 0.25});

        REQUIRE(interpolatedValue == Color(0.75f, 0.25f, 0.0f));
    }

    SECTION("should return the correct interpolated value for a point shared by multiple faces") {
        auto testData = GENERATE(table<int, Vector3f, Color>({{1, {0.0f, 0, 1.0f}, Color::createWhite()},
                                                              {2, {0.0f, 0.0f, 1.0f}, Color::createWhite()},
                                                              {0, {0.0f, 0.0f, 0.0f}, Color::createBlack()},
                                                              {3, {0.0f, 0.0f, 2.0f}, Color::createBlack()}}));

        TriangleMeshPerPointPrimVar<Color> primVar(*triangleMesh);
        primVar.allocate();
        primVar.write(1, Color::createWhite());

        Color interpolatedValueForFace1 = primVar.interpolateAt(std::get<0>(testData), std::get<1>(testData));

        REQUIRE(interpolatedValueForFace1 == std::get<2>(testData));
    }
}

TEST_CASE("TriangleMeshPerPointPrimVar::==") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    TriangleMeshPerPointPrimVar<Color> primVar(*triangleMesh);
    primVar.allocate();
    primVar.write(0, Color(1, 0, 0));
    primVar.write(1, Color(0, 1, 0));
    primVar.write(2, Color(0, 0, 1));
    primVar.write(3, Color(1, 0, 0));
    primVar.write(4, Color(0, 1, 0));
    primVar.write(5, Color(0, 0, 1));

    SECTION("primvar should be equal to equivalent buffer") {
        REQUIRE(primVar == std::vector<Color>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}}));
    }

    SECTION("primvar should not be equal to different equivalent buffer") {
        REQUIRE(primVar != std::vector<Color>());
    }
}

TEST_CASE("TriangleMeshPerPointPrimVar::apply") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    TriangleMeshPerPointPrimVar<Color> primVar(*triangleMesh);
    primVar.allocate();
    primVar.write(0, Color(1, 0, 0));
    primVar.write(1, Color(0, 1, 0));
    primVar.write(2, Color(0, 0, 1));
    primVar.write(3, Color(1, 0, 0));
    primVar.write(4, Color(0, 1, 0));
    primVar.write(5, Color(0, 0, 1));

    SECTION("should apply function to all elements") {
        primVar.apply([](Color color) { return color * 2; });

        REQUIRE(primVar == std::vector<Color>({{2, 0, 0}, {0, 2, 0}, {0, 0, 2}, {2, 0, 0}, {0, 2, 0}, {0, 0, 2}}));
    }
}

}