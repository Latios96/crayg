#include "scene/materials/ConstantShadingNodes.h"
#include "scene/materials/ConversionNodes.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("Vector2fToColor::evaluateColor") {

    SECTION("should convert Vector2f correctly") {
        auto vector2fConstant = std::make_shared<Vector2fConstant>(Vector2f(1, 2));
        Vector2fToColor vector2FToColor;
        vector2FToColor.vector2fInput.connectTo(vector2fConstant);

        auto color = vector2FToColor.evaluateColor(SurfaceInteraction({}, {}, {}));

        REQUIRE(color == Color(1, 2, 0));
    }
}

}