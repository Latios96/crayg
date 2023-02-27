#include "fixtures/TriangleMeshFixtures.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerFacePrimVar.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("TriangleMeshPerFacePrimVar::interpolateAt") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    SECTION("should interpolate constant value correctly") {
        TriangleMeshPerFacePrimVar<Color> primVar(*triangleMesh);
        primVar.allocate();
        primVar.write(0, Color::createGrey(0.5));
        primVar.write(1, Color::createGrey(0.5));
        primVar.write(2, Color::createGrey(0.5));
        primVar.write(3, Color::createGrey(0.5));

        Color interpolatedValue = primVar.interpolateAt(0, {-0.25, 0, 0.25});

        REQUIRE(interpolatedValue == Color::createGrey(0.5));
    }
}

TEST_CASE("TriangleMeshPerFacePrimVar::==") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    TriangleMeshPerFacePrimVar<Color> primVar(*triangleMesh);
    primVar.allocate();
    primVar.write(0, Color(1, 0, 0));
    primVar.write(1, Color(0, 1, 0));
    primVar.write(2, Color(0, 0, 1));
    primVar.write(3, Color(1, 1, 1));

    SECTION("primvar should be equal to equivalent buffer") {
        REQUIRE(primVar == std::vector<Color>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 1}}));
    }

    SECTION("primvar should not be equal to different equivalent buffer") {
        REQUIRE(primVar != std::vector<Color>());
    }
}

TEST_CASE("TriangleMeshPerFacePrimVar::apply") {
    auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();

    TriangleMeshPerFacePrimVar<Color> primVar(*triangleMesh);
    primVar.allocate();
    primVar.write(0, Color(1, 0, 0));
    primVar.write(1, Color(0, 1, 0));
    primVar.write(2, Color(0, 0, 1));
    primVar.write(3, Color(1, 1, 1));

    SECTION("should apply function to all elements") {
        primVar.apply([](Color color) { return color * 2; });

        REQUIRE(primVar == std::vector<Color>({{2, 0, 0}, {0, 2, 0}, {0, 0, 2}, {2, 2, 2}}));
    }
}

}