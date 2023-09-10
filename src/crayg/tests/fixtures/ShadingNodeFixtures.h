#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_SHADINGNODEFIXTURES_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_SHADINGNODEFIXTURES_H_

#include "scene/materials/Material.h"

namespace crayg {

class MyFloatShadingNode : public ShadingNode {
  public:
    std::string getType() override {
        return "MyFloatShadingNode";
    }

    ShadingNodeOutputType getOutputType() override {
        return FLOAT;
    }

    float evaluateFloat(const SurfaceInteraction &surfaceInteraction) override {
        return value;
    }

    float value;
};

class MyIntShadingNode : public ShadingNode {
  public:
    std::string getType() override {
        return "MyIntShadingNode";
    }

    ShadingNodeOutputType getOutputType() override {
        return INT;
    }

    int evaluateInt(const SurfaceInteraction &surfaceInteraction) override {
        return value;
    }

    int value;
};

class MyVector2fShadingNode : public ShadingNode {
  public:
    std::string getType() override {
        return "MyVector2fShadingNode";
    }

    ShadingNodeOutputType getOutputType() override {
        return VECTOR2F;
    }

    Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) override {
        return value;
    }

    Vector2f value;
};

class MyColorShadingNode : public ShadingNode {
  public:
    std::string getType() override {
        return "MyColorShadingNode";
    }

    ShadingNodeOutputType getOutputType() override {
        return COLOR;
    }

    Color evaluateColor(const SurfaceInteraction &surfaceInteraction) override {
        return {};
    }
};

class ShaderForTesting : public Material {
  public:
    ShaderForTesting();

    ColorShadingNodeInput colorInput;
    FloatShadingNodeInput reflectivity;
};
} // crayg

#endif // CRAYG_SRC_CRAYG_TESTS_FIXTURES_SHADINGNODEFIXTURES_H_
