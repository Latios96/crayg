#include "fixtures/TriangleMeshFixtures.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("TriangleMeshPerVertexPrimVar::interpolateAt") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    SECTION("should interpolate constant value correctly") {
        TriangleMeshPerVertexPrimVar<Color> primVar(*triangleMesh);
        primVar.allocate();
        primVar.write(0, VertexData(Color::createGrey(0.5)));
        primVar.write(1, VertexData(Color::createGrey(0.5)));

        Color interpolatedValue = primVar.interpolateAt(0, {-0.25, 0, 0.25});

        REQUIRE(interpolatedValue == Color::createGrey(0.5));
    }

    SECTION("should return the correct interpolated value") {
        auto testData = GENERATE(table<int, Vector3f, Color>({{1, {0.0f, 0, 1.0f}, Color::createWhite()},
                                                              {1, {1.0f, 0, 1.0f}, Color::createBlack()},
                                                              {2, {0.0f, 0.0f, 1.0f}, Color::createBlack()},
                                                              {0, {0.0f, 0.0f, 0.0f}, Color::createBlack()},
                                                              {3, {0.0f, 0.0f, 2.0f}, Color::createBlack()}}));

        TriangleMeshPerVertexPrimVar<Color> primVar(*triangleMesh);
        primVar.allocate();
        primVar.write(1, {Color::createWhite(), Color::createBlack(), Color::createBlack()});

        Color interpolatedValueForFace1 = primVar.interpolateAt(std::get<0>(testData), std::get<1>(testData));

        REQUIRE(interpolatedValueForFace1 == std::get<2>(testData));
    }
}

TEST_CASE("TriangleMeshPerVertexPrimVar::==") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    TriangleMeshPerVertexPrimVar<Color> primVar(*triangleMesh);
    primVar.allocate();
    primVar.write(0, VertexData(Color::createGrey(0.5)));
    primVar.write(1, VertexData(Color::createGrey(0.5)));
    primVar.write(2, VertexData(Color::createGrey(0.5)));
    primVar.write(3, VertexData(Color::createGrey(0.5)));

    SECTION("primvar should be equal to equivalent buffer") {
        REQUIRE(primVar == std::vector<VertexData<Color>>(
                               {VertexData(Color::createGrey(0.5)), VertexData(Color::createGrey(0.5)),
                                VertexData(Color::createGrey(0.5)), VertexData(Color::createGrey(0.5))}));
    }

    SECTION("primvar should not be equal to different equivalent buffer") {
        REQUIRE(primVar != std::vector<VertexData<Color>>({VertexData(Color::createGrey(0.5))}));
    }
}

TEST_CASE("TriangleMeshPerVertexPrimVar::apply") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    TriangleMeshPerVertexPrimVar<Color> primVar(*triangleMesh);
    primVar.allocate();
    primVar.write(0, VertexData(Color::createGrey(0.5)));
    primVar.write(1, VertexData(Color::createGrey(0.5)));
    primVar.write(2, VertexData(Color::createGrey(0.5)));
    primVar.write(3, VertexData(Color::createGrey(0.5)));

    SECTION("should apply function to all elements") {
        primVar.apply([](Color color) { return color * 2; });

        REQUIRE(primVar ==
                std::vector<VertexData<Color>>({VertexData(Color::createWhite()), VertexData(Color::createWhite()),
                                                VertexData(Color::createWhite()), VertexData(Color::createWhite())}));
    }
}

}