#include "scene/materials/ConstantShadingNodes.h"
#include "scene/materials/ShadingNode.h"
#include <catch2/catch.hpp>

namespace crayg {

class MyShadingNodeWithInputs : public ShadingNode {
  public:
    std::string getType() override {
        return "MyShadingNodeWithInputs";
    }

    ShadingNodeOutputType getOutputType() override {
        return COLOR;
    }

    IntShadingNodeInput intInput;
    FloatShadingNodeInput floatInput;
    Vector2fShadingNodeInput vector2fInput;
    ColorShadingNodeInput colorInput;
};

TEST_CASE("ShadingNodeInput::connect") {
    std::shared_ptr<ColorConstant> myColorShadingNode = std::make_shared<ColorConstant>();
    std::shared_ptr<IntConstant> myIntShadingNode = std::make_shared<IntConstant>();
    std::shared_ptr<FloatConstant> myFloatShadingNode = std::make_shared<FloatConstant>();
    std::shared_ptr<Vector2fConstant> myVector2FShadingNode = std::make_shared<Vector2fConstant>();
    std::shared_ptr<MyShadingNodeWithInputs> myShadingNodeWithInputs = std::make_shared<MyShadingNodeWithInputs>();

    SECTION("should connect FloatShadingNodeInput to float and int nodes") {
        myShadingNodeWithInputs->floatInput.connectTo(myFloatShadingNode);
        myShadingNodeWithInputs->floatInput.connectTo(myIntShadingNode);
    }

    SECTION("should not connect FloatShadingNodeInput to other nodes than float and int") {
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->floatInput.connectTo(myVector2FShadingNode), std::runtime_error);
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->floatInput.connectTo(myColorShadingNode), std::runtime_error);
    }

    SECTION("should connect IntShadingNodeInput to float and int nodes") {
        myShadingNodeWithInputs->intInput.connectTo(myFloatShadingNode);
        myShadingNodeWithInputs->intInput.connectTo(myIntShadingNode);
    }

    SECTION("should not connect IntShadingNodeInput to other nodes than float and int") {
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->intInput.connectTo(myVector2FShadingNode), std::runtime_error);
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->intInput.connectTo(myColorShadingNode), std::runtime_error);
    }

    SECTION("should connect Vector2fShadingNodeInput to Vector2f nodes") {
        myShadingNodeWithInputs->vector2fInput.connectTo(myVector2FShadingNode);
    }

    SECTION("should not connect Vector2fShadingNodeInput to other nodes than Vector2f") {
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->vector2fInput.connectTo(myIntShadingNode), std::runtime_error);
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->vector2fInput.connectTo(myFloatShadingNode), std::runtime_error);
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->vector2fInput.connectTo(myColorShadingNode), std::runtime_error);
    }

    SECTION("should connect ColorShadingNodeInput to Color nodes") {
        myShadingNodeWithInputs->colorInput.connectTo(myColorShadingNode);
    }

    SECTION("should not connect ColorShadingNodeInput to other nodes than Color") {
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->colorInput.connectTo(myIntShadingNode), std::runtime_error);
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->colorInput.connectTo(myFloatShadingNode), std::runtime_error);
        REQUIRE_THROWS_AS(myShadingNodeWithInputs->colorInput.connectTo(myVector2FShadingNode), std::runtime_error);
    }
}

TEST_CASE("ShadingNodeInput::evaluate") {
    std::shared_ptr<ColorConstant> myColorShadingNode = std::make_shared<ColorConstant>();
    std::shared_ptr<IntConstant> myIntShadingNode = std::make_shared<IntConstant>();
    std::shared_ptr<FloatConstant> myFloatShadingNode = std::make_shared<FloatConstant>();
    std::shared_ptr<Vector2fConstant> myVector2FShadingNode = std::make_shared<Vector2fConstant>();
    std::shared_ptr<MyShadingNodeWithInputs> myShadingNodeWithInputs = std::make_shared<MyShadingNodeWithInputs>();
    SurfaceInteraction surfaceInteraction({}, {}, {{}, {}});

    SECTION("should return connect input for FloatShadingNodeInput") {
        myShadingNodeWithInputs->floatInput.connectTo(myFloatShadingNode);
        myShadingNodeWithInputs->floatInput.value = 1;

        REQUIRE(myShadingNodeWithInputs->floatInput.evaluate(surfaceInteraction) == 0);
    }

    SECTION("should return connect input for IntShadingNodeInput") {
        myShadingNodeWithInputs->intInput.connectTo(myIntShadingNode);
        myShadingNodeWithInputs->intInput.value = 1;

        REQUIRE(myShadingNodeWithInputs->intInput.evaluate(surfaceInteraction) == 0);
    }

    SECTION("should return connect input for Vector2fShadingNodeInput") {
        myShadingNodeWithInputs->vector2fInput.connectTo(myVector2FShadingNode);
        myShadingNodeWithInputs->vector2fInput.value = {1, 1};

        REQUIRE(myShadingNodeWithInputs->vector2fInput.evaluate(surfaceInteraction) == Vector2f(0, 0));
    }

    SECTION("should return connect input for ColorShadingNodeInput") {
        myShadingNodeWithInputs->colorInput.connectTo(myColorShadingNode);
        myShadingNodeWithInputs->colorInput.value = Color::createWhite();

        REQUIRE(myShadingNodeWithInputs->colorInput.evaluate(surfaceInteraction) == Color::createBlack());
    }

    SECTION("should return default value because FloatShadingNodeInput is not connected") {
        myShadingNodeWithInputs->floatInput.value = 1;

        REQUIRE(myShadingNodeWithInputs->floatInput.evaluate(surfaceInteraction) == 1);
    }

    SECTION("should return default value because IntShadingNodeInput is not connected") {
        myShadingNodeWithInputs->intInput.value = 1;

        REQUIRE(myShadingNodeWithInputs->intInput.evaluate(surfaceInteraction) == 1);
    }

    SECTION("should return default value because  Vector2fShadingNodeInput is not connected") {
        myShadingNodeWithInputs->vector2fInput.value = {1, 1};

        REQUIRE(myShadingNodeWithInputs->vector2fInput.evaluate(surfaceInteraction) == Vector2f(1, 1));
    }

    SECTION("should return default value because  ColorShadingNodeInput is not connected") {
        myShadingNodeWithInputs->colorInput.value = Color::createWhite();

        REQUIRE(myShadingNodeWithInputs->colorInput.evaluate(surfaceInteraction) == Color::createWhite());
    }
}

TEST_CASE("ShadingNodeInput::hasInputConnection") {
    std::shared_ptr<ColorConstant> myColorShadingNode = std::make_shared<ColorConstant>();
    std::shared_ptr<MyShadingNodeWithInputs> myShadingNodeWithInputs = std::make_shared<MyShadingNodeWithInputs>();

    SECTION("should return true") {
        myShadingNodeWithInputs->colorInput.connectTo(myColorShadingNode);

        REQUIRE(myShadingNodeWithInputs->colorInput.hasInputConnection());
    }

    SECTION("should return false") {
        REQUIRE_FALSE(myShadingNodeWithInputs->colorInput.hasInputConnection());
    }
}

}