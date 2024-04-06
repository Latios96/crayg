#include "scene/primitives/Sphere.h"
#include "scene/shadingnetworks/shadingnodes/CheckerBoard.h"
#include <catch2/catch.hpp>

namespace crayg {

class UnitPlaneUvs : public ShadingNode {
  public:
    Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) override {
        return surfaceInteraction.point.xy();
    }

    std::string getType() const override {
        return "UnitPlaneUvs";
    }

    ShadingNodeOutputType getOutputType() override {
        return ShadingNodeOutputType::VECTOR2F;
    }
};

TEST_CASE("CheckerBoard::evaluateColor") {
    auto sphere = std::make_shared<Sphere>();
    auto unitPlaneUvs = std::make_shared<UnitPlaneUvs>();

    const Color colorA = Color(1, 0, 0);
    const Color colorB = Color(0, 1, 0);

    CheckerBoard checkerBoard;
    checkerBoard.repetitions = 2;
    checkerBoard.uvInput.connectTo(unitPlaneUvs);
    checkerBoard.colorA.value = colorA;
    checkerBoard.colorB.value = colorB;

    SECTION("should return colorA") {
        auto point = GENERATE(Vector2f(0, 0), Vector2f(0.25, 0), Vector2f(0, 0.25), Vector2f(0.25, 0.25),
                              Vector2f(0.49, 0.49), Vector2f(0.5, 0.5), Vector2f(0.6, 0.6), Vector2f(0.75, 0.75));

        auto color = checkerBoard.evaluateColor(SurfaceInteraction(*sphere, {point.x, point.y, 0}, {}, {}));

        REQUIRE(color == colorA);
    }

    SECTION("should return colorB") {
        auto point = GENERATE(Vector2f(0.51, 0), Vector2f(0.75, 0), Vector2f(0.51, 0.25), Vector2f(0.75, 0.25),
                              Vector2f(0.51, 0.49), Vector2f(0.6, 0.4), Vector2f(0.75, 0.25));

        auto color = checkerBoard.evaluateColor(SurfaceInteraction(*sphere, {point.x, point.y, 0}, {}, {}));

        REQUIRE(color == colorB);
    }

    SECTION("should respect repetitions and return colorA") {
        checkerBoard.repetitions = 4;
        auto point = GENERATE(Vector2f(0, 0), Vector2f(1, 0), Vector2f(0.51, 0));

        auto color = checkerBoard.evaluateColor(SurfaceInteraction(*sphere, {point.x, point.y, 0}, {}, {}));

        REQUIRE(color == colorA);
    }

    SECTION("should respect repetitions and return colorB") {
        checkerBoard.repetitions = 4;
        auto point = GENERATE(Vector2f(0.26, 0), Vector2f(0.76, 0.0), Vector2f(0.9, 0.0));

        auto color = checkerBoard.evaluateColor(SurfaceInteraction(*sphere, {point.x, point.y, 0}, {}, {}));

        REQUIRE(color == colorB);
    }
}

}