#include "crayg/scene/primitives/Sphere.h"
#include "crayg/scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h"
#include "crayg/scene/shadingnetworks/shadingnodes/ConversionNodes.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("Vector2fToColor::evaluateColor") {

    SECTION("should convert Vector2f correctly") {
        auto sphere = std::make_shared<Sphere>();
        auto vector2fConstant = std::make_shared<Vector2fConstant>(Vector2f(1, 2));
        Vector2fToColor vector2FToColor;
        vector2FToColor.vector2fInput.connectTo(vector2fConstant);

        auto color = vector2FToColor.evaluateColor(SurfaceInteraction(*sphere, {}, {}, {}));

        REQUIRE(color == Color(1, 2, 0));
    }
}

}