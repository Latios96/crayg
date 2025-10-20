#include "crayg/scene/primitives/Sphere.h"
#include "crayg/scene/shadingnetworks/shadingnodes/ColorToFloat.h"
#include "crayg/scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h"
#include "fixtures/UnitPlaneUvs.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ColorToFloat::evaluateFloat") {
    auto sphere = std::make_shared<Sphere>();
    auto unitPlaneUvs = std::make_shared<UnitPlaneUvs>();
    SurfaceInteraction surfaceInteraction(*sphere, {0, 0, 0}, {}, {});

    auto colorConstant = std::make_shared<ColorConstant>();
    colorConstant->value = Color(1, 2, 3);
    ColorToFloat colorToFloat;
    colorToFloat.colorInput.connectTo(colorConstant);

    SECTION("should return r") {
        colorToFloat.colorToFloatMode = ColorToFloatMode::R;
        const float evaluated = colorToFloat.evaluateFloat(surfaceInteraction);

        REQUIRE(evaluated == 1);
    }

    SECTION("should return g") {
        colorToFloat.colorToFloatMode = ColorToFloatMode::G;
        const float evaluated = colorToFloat.evaluateFloat(surfaceInteraction);

        REQUIRE(evaluated == 2);
    }

    SECTION("should return b") {
        colorToFloat.colorToFloatMode = ColorToFloatMode::B;
        const float evaluated = colorToFloat.evaluateFloat(surfaceInteraction);

        REQUIRE(evaluated == 3);
    }
}

}